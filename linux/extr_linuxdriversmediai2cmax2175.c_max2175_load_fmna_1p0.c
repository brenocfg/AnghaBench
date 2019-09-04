#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max2175 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* fmna1p0_map ; 
 int /*<<< orphan*/  max2175_write (struct max2175*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max2175_load_fmna_1p0(struct max2175 *ctx)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(fmna1p0_map); i++)
		max2175_write(ctx, fmna1p0_map[i].idx, fmna1p0_map[i].val);
}