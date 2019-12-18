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
struct usnic_vnic_res_chunk {int cnt; int type; struct usnic_vnic* vnic; struct usnic_vnic_res** res; int /*<<< orphan*/  free_cnt; } ;
struct usnic_vnic_res {void* owner; } ;
struct usnic_vnic {int /*<<< orphan*/  res_lock; struct usnic_vnic_res_chunk* chunks; } ;
typedef  enum usnic_vnic_res_type { ____Placeholder_usnic_vnic_res_type } usnic_vnic_res_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct usnic_vnic_res_chunk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct usnic_vnic_res** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usnic_vnic_res_chunk*) ; 
 struct usnic_vnic_res_chunk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int usnic_vnic_res_free_cnt (struct usnic_vnic*,int) ; 

struct usnic_vnic_res_chunk *
usnic_vnic_get_resources(struct usnic_vnic *vnic, enum usnic_vnic_res_type type,
				int cnt, void *owner)
{
	struct usnic_vnic_res_chunk *src, *ret;
	struct usnic_vnic_res *res;
	int i;

	if (usnic_vnic_res_free_cnt(vnic, type) < cnt || cnt < 0 || !owner)
		return ERR_PTR(-EINVAL);

	ret = kzalloc(sizeof(*ret), GFP_ATOMIC);
	if (!ret)
		return ERR_PTR(-ENOMEM);

	if (cnt > 0) {
		ret->res = kcalloc(cnt, sizeof(*(ret->res)), GFP_ATOMIC);
		if (!ret->res) {
			kfree(ret);
			return ERR_PTR(-ENOMEM);
		}

		spin_lock(&vnic->res_lock);
		src = &vnic->chunks[type];
		for (i = 0; i < src->cnt && ret->cnt < cnt; i++) {
			res = src->res[i];
			if (!res->owner) {
				src->free_cnt--;
				res->owner = owner;
				ret->res[ret->cnt++] = res;
			}
		}

		spin_unlock(&vnic->res_lock);
	}
	ret->type = type;
	ret->vnic = vnic;
	WARN_ON(ret->cnt != cnt);

	return ret;
}