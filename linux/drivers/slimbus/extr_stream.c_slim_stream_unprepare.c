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
struct slim_stream_runtime {int num_ports; int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slim_disconnect_port (struct slim_stream_runtime*,int /*<<< orphan*/ *) ; 

int slim_stream_unprepare(struct slim_stream_runtime *stream)
{
	int i;

	for (i = 0; i < stream->num_ports; i++)
		slim_disconnect_port(stream, &stream->ports[i]);

	kfree(stream->ports);
	stream->ports = NULL;
	stream->num_ports = 0;

	return 0;
}