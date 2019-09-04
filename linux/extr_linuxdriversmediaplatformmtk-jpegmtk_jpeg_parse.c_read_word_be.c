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
typedef  int u32 ;
struct mtk_jpeg_stream {int dummy; } ;

/* Variables and functions */
 int read_byte (struct mtk_jpeg_stream*) ; 

__attribute__((used)) static int read_word_be(struct mtk_jpeg_stream *stream, u32 *word)
{
	u32 temp;
	int byte;

	byte = read_byte(stream);
	if (byte == -1)
		return -1;
	temp = byte << 8;
	byte = read_byte(stream);
	if (byte == -1)
		return -1;
	*word = (u32)byte | temp;

	return 0;
}