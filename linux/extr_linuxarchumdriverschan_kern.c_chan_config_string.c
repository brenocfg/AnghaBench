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
struct line {struct chan* chan_out; struct chan* chan_in; } ;
struct chan {int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 int chan_pair_config_string (struct chan*,struct chan*,char*,int,char**) ; 

int chan_config_string(struct line *line, char *str, int size,
		       char **error_out)
{
	struct chan *in = line->chan_in, *out = line->chan_out;

	if (in && !in->primary)
		in = NULL;
	if (out && !out->primary)
		out = NULL;

	return chan_pair_config_string(in, out, str, size, error_out);
}