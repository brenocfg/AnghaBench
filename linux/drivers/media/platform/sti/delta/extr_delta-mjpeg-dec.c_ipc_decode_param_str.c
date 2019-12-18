#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int display_decimated_luma_p; int display_decimated_chroma_p; } ;
struct jpeg_decode_params_t {int picture_start_addr_p; int picture_end_addr_p; int decoding_mode; int main_aux_enable; int additional_flags; int field_flag; int is_jpeg_image; TYPE_1__ display_buffer_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static char *ipc_decode_param_str(struct jpeg_decode_params_t *p,
				  char *str, unsigned int len)
{
	char *b = str;

	if (!p)
		return "";

	b += snprintf(b, len,
		      "jpeg_decode_params_t\n"
		      "picture_start_addr_p                  0x%x\n"
		      "picture_end_addr_p                    0x%x\n"
		      "decoding_mode                        %d\n"
		      "display_buffer_addr.display_decimated_luma_p   0x%x\n"
		      "display_buffer_addr.display_decimated_chroma_p 0x%x\n"
		      "main_aux_enable                       %d\n"
		      "additional_flags                     0x%x\n"
		      "field_flag                           %x\n"
		      "is_jpeg_image                        %x\n",
		      p->picture_start_addr_p,
		      p->picture_end_addr_p,
		      p->decoding_mode,
		      p->display_buffer_addr.display_decimated_luma_p,
		      p->display_buffer_addr.display_decimated_chroma_p,
		      p->main_aux_enable, p->additional_flags,
		      p->field_flag,
		      p->is_jpeg_image);

	return str;
}