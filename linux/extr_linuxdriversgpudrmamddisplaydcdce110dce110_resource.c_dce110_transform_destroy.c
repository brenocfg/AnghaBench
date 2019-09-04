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
struct transform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TO_DCE_TRANSFORM (struct transform*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_transform_destroy(struct transform **xfm)
{
	kfree(TO_DCE_TRANSFORM(*xfm));
	*xfm = NULL;
}