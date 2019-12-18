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
struct lp8788_platform_data {int (* init_func ) (struct lp8788*) ;} ;
struct lp8788 {struct lp8788_platform_data* pdata; } ;

/* Variables and functions */
 int stub1 (struct lp8788*) ; 

__attribute__((used)) static int lp8788_platform_init(struct lp8788 *lp)
{
	struct lp8788_platform_data *pdata = lp->pdata;

	return (pdata && pdata->init_func) ? pdata->init_func(lp) : 0;
}