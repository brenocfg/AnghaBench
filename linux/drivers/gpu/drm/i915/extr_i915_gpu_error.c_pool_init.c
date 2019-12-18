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
struct pagevec {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int /*<<< orphan*/  pool_fini (struct pagevec*) ; 
 int pool_refill (struct pagevec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pool_init(struct pagevec *pv, gfp_t gfp)
{
	int err;

	pagevec_init(pv);

	err = pool_refill(pv, gfp);
	if (err)
		pool_fini(pv);

	return err;
}