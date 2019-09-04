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
struct jpeg_video_decode_init_params_t {int circular_buffer_begin_addr_p; int circular_buffer_end_addr_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,int,int) ; 

__attribute__((used)) static char *ipc_open_param_str(struct jpeg_video_decode_init_params_t *p,
				char *str, unsigned int len)
{
	char *b = str;

	if (!p)
		return "";

	b += snprintf(b, len,
		      "jpeg_video_decode_init_params_t\n"
		      "circular_buffer_begin_addr_p 0x%x\n"
		      "circular_buffer_end_addr_p   0x%x\n",
		      p->circular_buffer_begin_addr_p,
		      p->circular_buffer_end_addr_p);

	return str;
}