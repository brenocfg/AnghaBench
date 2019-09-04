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
struct ib_pd {int dummy; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

struct ib_mr *usnic_ib_get_dma_mr(struct ib_pd *pd, int acc)
{
	usnic_dbg("\n");
	return ERR_PTR(-ENOMEM);
}