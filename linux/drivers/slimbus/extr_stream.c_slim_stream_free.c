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
struct slim_stream_runtime {struct slim_stream_runtime* name; int /*<<< orphan*/  node; struct slim_device* dev; } ;
struct slim_device {int /*<<< orphan*/  stream_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct slim_stream_runtime*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int slim_stream_free(struct slim_stream_runtime *stream)
{
	struct slim_device *sdev = stream->dev;

	spin_lock(&sdev->stream_list_lock);
	list_del(&stream->node);
	spin_unlock(&sdev->stream_list_lock);

	kfree(stream->name);
	kfree(stream);

	return 0;
}