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
struct mtk_jpeg_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_byte (struct mtk_jpeg_stream*) ; 

__attribute__((used)) static void read_skip(struct mtk_jpeg_stream *stream, long len)
{
	if (len <= 0)
		return;
	while (len--)
		read_byte(stream);
}