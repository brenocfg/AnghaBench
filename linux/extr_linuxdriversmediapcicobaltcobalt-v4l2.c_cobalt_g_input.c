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
struct file {int dummy; } ;
struct cobalt_stream {unsigned int input; } ;

/* Variables and functions */
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_g_input(struct file *file, void *priv_fh, unsigned int *i)
{
	struct cobalt_stream *s = video_drvdata(file);

	*i = s->input;
	return 0;
}