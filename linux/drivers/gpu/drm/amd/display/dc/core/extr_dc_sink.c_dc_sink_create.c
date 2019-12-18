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
struct dc_sink_init_data {int dummy; } ;
struct dc_sink {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int construct (struct dc_sink*,struct dc_sink_init_data const*) ; 
 int /*<<< orphan*/  kfree (struct dc_sink*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dc_sink* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dc_sink *dc_sink_create(const struct dc_sink_init_data *init_params)
{
	struct dc_sink *sink = kzalloc(sizeof(*sink), GFP_KERNEL);

	if (NULL == sink)
		goto alloc_fail;

	if (false == construct(sink, init_params))
		goto construct_fail;

	kref_init(&sink->refcount);

	return sink;

construct_fail:
	kfree(sink);

alloc_fail:
	return NULL;
}