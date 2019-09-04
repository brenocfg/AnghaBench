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
 int /*<<< orphan*/  destruct (struct aux_engine_dce110*) ; 
 int /*<<< orphan*/  kfree (struct aux_engine_dce110*) ; 

__attribute__((used)) static void destroy(
	struct aux_engine **aux_engine)
{
	struct aux_engine_dce110 *engine = FROM_AUX_ENGINE(*aux_engine);

	destruct(engine);

	kfree(engine);

	*aux_engine = NULL;
}