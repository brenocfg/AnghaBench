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
struct iser_fr_desc {int dummy; } ;
struct ib_conn {int dummy; } ;

/* Variables and functions */

void
iser_reg_desc_put_fmr(struct ib_conn *ib_conn,
		      struct iser_fr_desc *desc)
{
}