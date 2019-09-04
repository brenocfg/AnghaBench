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
struct ocxl_afu {int /*<<< orphan*/  fn; int /*<<< orphan*/  contexts_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ocxl_afu*) ; 
 int /*<<< orphan*/  ocxl_fn_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_afu(struct ocxl_afu *afu)
{
	idr_destroy(&afu->contexts_idr);
	ocxl_fn_put(afu->fn);
	kfree(afu);
}