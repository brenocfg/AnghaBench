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
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  ldc_unmap (struct ldc_channel*,struct ldc_trans_cookie*,int) ; 

void ldc_free_exp_dring(struct ldc_channel *lp, void *buf, unsigned int len,
			struct ldc_trans_cookie *cookies, int ncookies)
{
	ldc_unmap(lp, cookies, ncookies);
	kfree(buf);
}