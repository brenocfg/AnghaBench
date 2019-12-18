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
struct sdw_stream_runtime {char const* name; scalar_t__ m_rt_count; int /*<<< orphan*/  state; int /*<<< orphan*/  master_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDW_STREAM_ALLOCATED ; 
 struct sdw_stream_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 

struct sdw_stream_runtime *sdw_alloc_stream(const char *stream_name)
{
	struct sdw_stream_runtime *stream;

	stream = kzalloc(sizeof(*stream), GFP_KERNEL);
	if (!stream)
		return NULL;

	stream->name = stream_name;
	INIT_LIST_HEAD(&stream->master_list);
	stream->state = SDW_STREAM_ALLOCATED;
	stream->m_rt_count = 0;

	return stream;
}