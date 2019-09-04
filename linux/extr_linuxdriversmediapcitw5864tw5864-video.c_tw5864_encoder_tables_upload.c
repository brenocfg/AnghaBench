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
struct tw5864_dev {int dummy; } ;

/* Variables and functions */
 int QUANTIZATION_TABLE_LEN ; 
 scalar_t__ TW5864_QUAN_TAB ; 
 scalar_t__ TW5864_VLC_RD ; 
 scalar_t__ TW5864_VLC_STREAM_MEM_START ; 
 int VLC_LOOKUP_TABLE_LEN ; 
 int* encoder_vlc_lookup_table ; 
 int* forward_quantization_table ; 
 int* inverse_quantization_table ; 
 int /*<<< orphan*/  tw_writel (scalar_t__,int) ; 

__attribute__((used)) static void tw5864_encoder_tables_upload(struct tw5864_dev *dev)
{
	int i;

	tw_writel(TW5864_VLC_RD, 0x1);
	for (i = 0; i < VLC_LOOKUP_TABLE_LEN; i++) {
		tw_writel((TW5864_VLC_STREAM_MEM_START + i * 4),
			  encoder_vlc_lookup_table[i]);
	}
	tw_writel(TW5864_VLC_RD, 0x0);

	for (i = 0; i < QUANTIZATION_TABLE_LEN; i++) {
		tw_writel((TW5864_QUAN_TAB + i * 4),
			  forward_quantization_table[i]);
	}

	for (i = 0; i < QUANTIZATION_TABLE_LEN; i++) {
		tw_writel((TW5864_QUAN_TAB + i * 4),
			  inverse_quantization_table[i]);
	}
}