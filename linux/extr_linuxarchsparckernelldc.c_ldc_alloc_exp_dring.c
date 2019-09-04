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
struct ldc_trans_cookie {int dummy; } ;
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int ldc_map_single (struct ldc_channel*,void*,unsigned int,struct ldc_trans_cookie*,int,unsigned int) ; 

void *ldc_alloc_exp_dring(struct ldc_channel *lp, unsigned int len,
			  struct ldc_trans_cookie *cookies, int *ncookies,
			  unsigned int map_perm)
{
	void *buf;
	int err;

	if (len & (8UL - 1))
		return ERR_PTR(-EINVAL);

	buf = kzalloc(len, GFP_ATOMIC);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	err = ldc_map_single(lp, buf, len, cookies, *ncookies, map_perm);
	if (err < 0) {
		kfree(buf);
		return ERR_PTR(err);
	}
	*ncookies = err;

	return buf;
}