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
struct sdw_stream_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sdw_stream_runtime*) ; 

void sdw_release_stream(struct sdw_stream_runtime *stream)
{
	kfree(stream);
}