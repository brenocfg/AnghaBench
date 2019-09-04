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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int USBTV_CHUNK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void usbtv_chunk_to_vbuf(u32 *frame, __be32 *src, int chunk_no, int odd)
{
	int half;

	for (half = 0; half < 2; half++) {
		int part_no = chunk_no * 2 + half;
		int line = part_no / 3;
		int part_index = (line * 2 + !odd) * 3 + (part_no % 3);

		u32 *dst = &frame[part_index * USBTV_CHUNK/2];

		memcpy(dst, src, USBTV_CHUNK/2 * sizeof(*src));
		src += USBTV_CHUNK/2;
	}
}