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
struct aspeed_video {unsigned int max_compressed_size; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  VE_STREAM_BUF_SIZE ; 
 int /*<<< orphan*/  aspeed_video_write (struct aspeed_video*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void aspeed_video_calc_compressed_size(struct aspeed_video *video,
					      unsigned int frame_size)
{
	int i, j;
	u32 compression_buffer_size_reg = 0;
	unsigned int size;
	const unsigned int num_compression_packets = 4;
	const unsigned int compression_packet_size = 1024;
	const unsigned int max_compressed_size = frame_size / 2; /* 4bpp / 8 */

	video->max_compressed_size = UINT_MAX;

	for (i = 0; i < 6; ++i) {
		for (j = 0; j < 8; ++j) {
			size = (num_compression_packets << i) *
				(compression_packet_size << j);
			if (size < max_compressed_size)
				continue;

			if (size < video->max_compressed_size) {
				compression_buffer_size_reg = (i << 3) | j;
				video->max_compressed_size = size;
			}
		}
	}

	aspeed_video_write(video, VE_STREAM_BUF_SIZE,
			   compression_buffer_size_reg);

	dev_dbg(video->dev, "Max compressed size: %x\n",
		video->max_compressed_size);
}