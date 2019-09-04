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
struct aux_engine_dce110_init_data {int dummy; } ;
struct aux_engine {int dummy; } ;
struct aux_engine_dce110 {struct aux_engine base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (struct aux_engine_dce110*,struct aux_engine_dce110_init_data const*) ; 
 struct aux_engine_dce110* kzalloc (int,int /*<<< orphan*/ ) ; 

struct aux_engine *dal_aux_engine_dce110_create(
	const struct aux_engine_dce110_init_data *aux_init_data)
{
	struct aux_engine_dce110 *engine;

	if (!aux_init_data) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	engine = kzalloc(sizeof(*engine), GFP_KERNEL);

	if (!engine) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	construct(engine, aux_init_data);
	return &engine->base;
}