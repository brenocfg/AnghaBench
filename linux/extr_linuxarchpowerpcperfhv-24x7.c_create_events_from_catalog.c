#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct rb_root {int dummy; } ;
struct hv_24x7_event_data {scalar_t__ event_group_record_len; int /*<<< orphan*/  domain; int /*<<< orphan*/  length; } ;
struct hv_24x7_catalog_page_0 {int /*<<< orphan*/  event_data_len; int /*<<< orphan*/  event_data_offs; int /*<<< orphan*/  event_entry_count; int /*<<< orphan*/  length; int /*<<< orphan*/  version; } ;
struct attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_4K ; 
 int PAGE_SIZE ; 
 struct rb_root RB_ROOT ; 
 int SIZE_MAX ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catalog_entry_domain_is_valid (int /*<<< orphan*/ ) ; 
 size_t catalog_event_len_validate (struct hv_24x7_event_data*,size_t,size_t,size_t,size_t,void*) ; 
 size_t event_data_to_attrs (size_t,struct attribute**,struct hv_24x7_event_data*,int) ; 
 char* event_name (struct hv_24x7_event_data*,int*) ; 
 struct attribute* event_to_desc_attr (struct hv_24x7_event_data*,int) ; 
 struct attribute* event_to_long_desc_attr (struct hv_24x7_event_data*,int) ; 
 int event_uniq_add (struct rb_root*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_uniq_destroy (struct rb_root*) ; 
 long h_get_24x7_catalog_page (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long h_get_24x7_catalog_page_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  hv_page_cache ; 
 int /*<<< orphan*/  kfree (struct attribute**) ; 
 struct attribute** kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 
 struct hv_24x7_catalog_page_0* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pr_devel (char*,size_t,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,size_t,...) ; 
 int /*<<< orphan*/  pr_warn (char*,size_t,int,...) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (size_t) ; 
 int /*<<< orphan*/  vmalloc_to_phys (void*) ; 

__attribute__((used)) static int create_events_from_catalog(struct attribute ***events_,
				      struct attribute ***event_descs_,
				      struct attribute ***event_long_descs_)
{
	long hret;
	size_t catalog_len, catalog_page_len, event_entry_count,
	       event_data_len, event_data_offs,
	       event_data_bytes, junk_events, event_idx, event_attr_ct, i,
	       attr_max, event_idx_last, desc_ct, long_desc_ct;
	ssize_t ct, ev_len;
	uint64_t catalog_version_num;
	struct attribute **events, **event_descs, **event_long_descs;
	struct hv_24x7_catalog_page_0 *page_0 =
		kmem_cache_alloc(hv_page_cache, GFP_KERNEL);
	void *page = page_0;
	void *event_data, *end;
	struct hv_24x7_event_data *event;
	struct rb_root ev_uniq = RB_ROOT;
	int ret = 0;

	if (!page) {
		ret = -ENOMEM;
		goto e_out;
	}

	hret = h_get_24x7_catalog_page(page, 0, 0);
	if (hret) {
		ret = -EIO;
		goto e_free;
	}

	catalog_version_num = be64_to_cpu(page_0->version);
	catalog_page_len = be32_to_cpu(page_0->length);

	if (MAX_4K < catalog_page_len) {
		pr_err("invalid page count: %zu\n", catalog_page_len);
		ret = -EIO;
		goto e_free;
	}

	catalog_len = catalog_page_len * 4096;

	event_entry_count = be16_to_cpu(page_0->event_entry_count);
	event_data_offs   = be16_to_cpu(page_0->event_data_offs);
	event_data_len    = be16_to_cpu(page_0->event_data_len);

	pr_devel("cv %llu cl %zu eec %zu edo %zu edl %zu\n",
			catalog_version_num, catalog_len,
			event_entry_count, event_data_offs, event_data_len);

	if ((MAX_4K < event_data_len)
			|| (MAX_4K < event_data_offs)
			|| (MAX_4K - event_data_offs < event_data_len)) {
		pr_err("invalid event data offs %zu and/or len %zu\n",
				event_data_offs, event_data_len);
		ret = -EIO;
		goto e_free;
	}

	if ((event_data_offs + event_data_len) > catalog_page_len) {
		pr_err("event data %zu-%zu does not fit inside catalog 0-%zu\n",
				event_data_offs,
				event_data_offs + event_data_len,
				catalog_page_len);
		ret = -EIO;
		goto e_free;
	}

	if (SIZE_MAX - 1 < event_entry_count) {
		pr_err("event_entry_count %zu is invalid\n", event_entry_count);
		ret = -EIO;
		goto e_free;
	}

	event_data_bytes = event_data_len * 4096;

	/*
	 * event data can span several pages, events can cross between these
	 * pages. Use vmalloc to make this easier.
	 */
	event_data = vmalloc(event_data_bytes);
	if (!event_data) {
		pr_err("could not allocate event data\n");
		ret = -ENOMEM;
		goto e_free;
	}

	end = event_data + event_data_bytes;

	/*
	 * using vmalloc_to_phys() like this only works if PAGE_SIZE is
	 * divisible by 4096
	 */
	BUILD_BUG_ON(PAGE_SIZE % 4096);

	for (i = 0; i < event_data_len; i++) {
		hret = h_get_24x7_catalog_page_(
				vmalloc_to_phys(event_data + i * 4096),
				catalog_version_num,
				i + event_data_offs);
		if (hret) {
			pr_err("Failed to get event data in page %zu: rc=%ld\n",
			       i + event_data_offs, hret);
			ret = -EIO;
			goto e_event_data;
		}
	}

	/*
	 * scan the catalog to determine the number of attributes we need, and
	 * verify it at the same time.
	 */
	for (junk_events = 0, event = event_data, event_idx = 0, attr_max = 0;
	     ;
	     event_idx++, event = (void *)event + ev_len) {
		size_t offset = (void *)event - (void *)event_data;
		char *name;
		int nl;

		ev_len = catalog_event_len_validate(event, event_idx,
						    event_data_bytes,
						    event_entry_count,
						    offset, end);
		if (ev_len < 0)
			break;

		name = event_name(event, &nl);

		if (event->event_group_record_len == 0) {
			pr_devel("invalid event %zu (%.*s): group_record_len == 0, skipping\n",
					event_idx, nl, name);
			junk_events++;
			continue;
		}

		if (!catalog_entry_domain_is_valid(event->domain)) {
			pr_info("event %zu (%.*s) has invalid domain %d\n",
					event_idx, nl, name, event->domain);
			junk_events++;
			continue;
		}

		attr_max++;
	}

	event_idx_last = event_idx;
	if (event_idx_last != event_entry_count)
		pr_warn("event buffer ended before listed # of events were parsed (got %zu, wanted %zu, junk %zu)\n",
				event_idx_last, event_entry_count, junk_events);

	events = kmalloc_array(attr_max + 1, sizeof(*events), GFP_KERNEL);
	if (!events) {
		ret = -ENOMEM;
		goto e_event_data;
	}

	event_descs = kmalloc_array(event_idx + 1, sizeof(*event_descs),
				GFP_KERNEL);
	if (!event_descs) {
		ret = -ENOMEM;
		goto e_event_attrs;
	}

	event_long_descs = kmalloc_array(event_idx + 1,
			sizeof(*event_long_descs), GFP_KERNEL);
	if (!event_long_descs) {
		ret = -ENOMEM;
		goto e_event_descs;
	}

	/* Iterate over the catalog filling in the attribute vector */
	for (junk_events = 0, event_attr_ct = 0, desc_ct = 0, long_desc_ct = 0,
				event = event_data, event_idx = 0;
			event_idx < event_idx_last;
			event_idx++, ev_len = be16_to_cpu(event->length),
				event = (void *)event + ev_len) {
		char *name;
		int nl;
		int nonce;
		/*
		 * these are the only "bad" events that are intermixed and that
		 * we can ignore without issue. make sure to skip them here
		 */
		if (event->event_group_record_len == 0)
			continue;
		if (!catalog_entry_domain_is_valid(event->domain))
			continue;

		name  = event_name(event, &nl);
		nonce = event_uniq_add(&ev_uniq, name, nl, event->domain);
		ct    = event_data_to_attrs(event_idx, events + event_attr_ct,
					    event, nonce);
		if (ct < 0) {
			pr_warn("event %zu (%.*s) creation failure, skipping\n",
				event_idx, nl, name);
			junk_events++;
		} else {
			event_attr_ct++;
			event_descs[desc_ct] = event_to_desc_attr(event, nonce);
			if (event_descs[desc_ct])
				desc_ct++;
			event_long_descs[long_desc_ct] =
					event_to_long_desc_attr(event, nonce);
			if (event_long_descs[long_desc_ct])
				long_desc_ct++;
		}
	}

	pr_info("read %zu catalog entries, created %zu event attrs (%zu failures), %zu descs\n",
			event_idx, event_attr_ct, junk_events, desc_ct);

	events[event_attr_ct] = NULL;
	event_descs[desc_ct] = NULL;
	event_long_descs[long_desc_ct] = NULL;

	event_uniq_destroy(&ev_uniq);
	vfree(event_data);
	kmem_cache_free(hv_page_cache, page);

	*events_ = events;
	*event_descs_ = event_descs;
	*event_long_descs_ = event_long_descs;
	return 0;

e_event_descs:
	kfree(event_descs);
e_event_attrs:
	kfree(events);
e_event_data:
	vfree(event_data);
e_free:
	kmem_cache_free(hv_page_cache, page);
e_out:
	*events_ = NULL;
	*event_descs_ = NULL;
	*event_long_descs_ = NULL;
	return ret;
}