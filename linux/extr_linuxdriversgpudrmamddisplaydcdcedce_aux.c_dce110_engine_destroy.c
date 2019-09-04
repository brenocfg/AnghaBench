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
struct aux_engine_dce110 {int dummy; } ;
struct aux_engine {int dummy; } ;

/* Variables and functions */
 struct aux_engine_dce110* FROM_AUX_ENGINE (struct aux_engine*) ; 
 int /*<<< orphan*/  kfree (struct aux_engine_dce110*) ; 

void dce110_engine_destroy(struct aux_engine **engine)
{

	struct aux_engine_dce110 *engine110 = FROM_AUX_ENGINE(*engine);

	kfree(engine110);
	*engine = NULL;

}