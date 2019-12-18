#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pstore {scalar_t__ current_area; TYPE_1__* store; int /*<<< orphan*/  area; } ;
typedef  void dm_bufio_client ;
struct dm_buffer {int dummy; } ;
typedef  scalar_t__ chunk_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int chunk_size; int /*<<< orphan*/  snap; } ;

/* Variables and functions */
 scalar_t__ DM_PREFETCH_CHUNKS ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SECTOR_SHIFT ; 
 scalar_t__ area_location (struct pstore*,scalar_t__) ; 
 void* dm_bufio_client_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_bufio_client_destroy (void*) ; 
 int /*<<< orphan*/  dm_bufio_forget (void*,scalar_t__) ; 
 scalar_t__ dm_bufio_get_device_size (void*) ; 
 int /*<<< orphan*/  dm_bufio_prefetch (void*,scalar_t__,int) ; 
 void* dm_bufio_read (void*,scalar_t__,struct dm_buffer**) ; 
 int /*<<< orphan*/  dm_bufio_release (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_set_minimum_buffers (void*,scalar_t__) ; 
 TYPE_2__* dm_snap_cow (int /*<<< orphan*/ ) ; 
 int insert_exceptions (struct pstore*,void*,int (*) (void*,chunk_t,chunk_t),void*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  skip_metadata (struct pstore*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int read_exceptions(struct pstore *ps,
			   int (*callback)(void *callback_context, chunk_t old,
					   chunk_t new),
			   void *callback_context)
{
	int r, full = 1;
	struct dm_bufio_client *client;
	chunk_t prefetch_area = 0;

	client = dm_bufio_client_create(dm_snap_cow(ps->store->snap)->bdev,
					ps->store->chunk_size << SECTOR_SHIFT,
					1, 0, NULL, NULL);

	if (IS_ERR(client))
		return PTR_ERR(client);

	/*
	 * Setup for one current buffer + desired readahead buffers.
	 */
	dm_bufio_set_minimum_buffers(client, 1 + DM_PREFETCH_CHUNKS);

	/*
	 * Keeping reading chunks and inserting exceptions until
	 * we find a partially full area.
	 */
	for (ps->current_area = 0; full; ps->current_area++) {
		struct dm_buffer *bp;
		void *area;
		chunk_t chunk;

		if (unlikely(prefetch_area < ps->current_area))
			prefetch_area = ps->current_area;

		if (DM_PREFETCH_CHUNKS) do {
			chunk_t pf_chunk = area_location(ps, prefetch_area);
			if (unlikely(pf_chunk >= dm_bufio_get_device_size(client)))
				break;
			dm_bufio_prefetch(client, pf_chunk, 1);
			prefetch_area++;
			if (unlikely(!prefetch_area))
				break;
		} while (prefetch_area <= ps->current_area + DM_PREFETCH_CHUNKS);

		chunk = area_location(ps, ps->current_area);

		area = dm_bufio_read(client, chunk, &bp);
		if (IS_ERR(area)) {
			r = PTR_ERR(area);
			goto ret_destroy_bufio;
		}

		r = insert_exceptions(ps, area, callback, callback_context,
				      &full);

		if (!full)
			memcpy(ps->area, area, ps->store->chunk_size << SECTOR_SHIFT);

		dm_bufio_release(bp);

		dm_bufio_forget(client, chunk);

		if (unlikely(r))
			goto ret_destroy_bufio;
	}

	ps->current_area--;

	skip_metadata(ps);

	r = 0;

ret_destroy_bufio:
	dm_bufio_client_destroy(client);

	return r;
}