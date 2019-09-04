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
struct dc_gamma {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_gamma_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dc_gamma_release(struct dc_gamma **gamma)
{
	kref_put(&(*gamma)->refcount, dc_gamma_free);
	*gamma = NULL;
}