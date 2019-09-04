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
struct chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CHUNK (char*,int,int,char*,int) ; 
 int one_chan_config_string (struct chan*,char*,int,char**) ; 

__attribute__((used)) static int chan_pair_config_string(struct chan *in, struct chan *out,
				   char *str, int size, char **error_out)
{
	int n;

	n = one_chan_config_string(in, str, size, error_out);
	str += n;
	size -= n;

	if (in == out) {
		CONFIG_CHUNK(str, size, n, "", 1);
		return n;
	}

	CONFIG_CHUNK(str, size, n, ",", 1);
	n = one_chan_config_string(out, str, size, error_out);
	str += n;
	size -= n;
	CONFIG_CHUNK(str, size, n, "", 1);

	return n;
}