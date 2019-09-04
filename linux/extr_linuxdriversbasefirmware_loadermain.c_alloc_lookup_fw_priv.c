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
struct fw_priv {int /*<<< orphan*/  list; int /*<<< orphan*/  ref; } ;
struct firmware_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
typedef  enum fw_opt { ____Placeholder_fw_opt } fw_opt ;

/* Variables and functions */
 int ENOMEM ; 
 int FW_OPT_NOCACHE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct fw_priv* __allocate_fw_priv (char const*,struct firmware_cache*,void*,size_t) ; 
 struct fw_priv* __lookup_fw_priv (char const*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_lookup_fw_priv(const char *fw_name,
				struct firmware_cache *fwc,
				struct fw_priv **fw_priv, void *dbuf,
				size_t size, enum fw_opt opt_flags)
{
	struct fw_priv *tmp;

	spin_lock(&fwc->lock);
	if (!(opt_flags & FW_OPT_NOCACHE)) {
		tmp = __lookup_fw_priv(fw_name);
		if (tmp) {
			kref_get(&tmp->ref);
			spin_unlock(&fwc->lock);
			*fw_priv = tmp;
			pr_debug("batched request - sharing the same struct fw_priv and lookup for multiple requests\n");
			return 1;
		}
	}

	tmp = __allocate_fw_priv(fw_name, fwc, dbuf, size);
	if (tmp) {
		INIT_LIST_HEAD(&tmp->list);
		if (!(opt_flags & FW_OPT_NOCACHE))
			list_add(&tmp->list, &fwc->head);
	}
	spin_unlock(&fwc->lock);

	*fw_priv = tmp;

	return tmp ? 0 : -ENOMEM;
}