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
typedef  int u8 ;
typedef  int u16 ;
struct go7007 {scalar_t__ interlace_coding; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BFRAME_BIDIR ; 
 int /*<<< orphan*/  BFRAME_POST ; 
 int /*<<< orphan*/  BFRAME_PRE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PFRAME ; 
 scalar_t__ __cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int*,int) ; 
 int mpeg1_frame_header (struct go7007*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpeg1_sequence_header (struct go7007*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen_mpeg1hdr_to_package(struct go7007 *go,
					__le16 *code, int space, int *framelen)
{
	u8 *buf;
	u16 mem = 0x3e00;
	unsigned int addr = 0x19;
	int i, off = 0, chunk;

	buf = kzalloc(5120, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	framelen[0] = mpeg1_frame_header(go, buf, 0, 1, PFRAME);
	if (go->interlace_coding)
		framelen[0] += mpeg1_frame_header(go, buf + framelen[0] / 8,
							0, 2, PFRAME);
	buf[0] = framelen[0] & 0xff;
	buf[1] = framelen[0] >> 8;
	i = 368;
	framelen[1] = mpeg1_frame_header(go, buf + i, 0, 1, BFRAME_PRE);
	if (go->interlace_coding)
		framelen[1] += mpeg1_frame_header(go, buf + i + framelen[1] / 8,
							0, 2, BFRAME_PRE);
	buf[i] = framelen[1] & 0xff;
	buf[i + 1] = framelen[1] >> 8;
	i += 1632;
	framelen[2] = mpeg1_frame_header(go, buf + i, 0, 1, BFRAME_POST);
	if (go->interlace_coding)
		framelen[2] += mpeg1_frame_header(go, buf + i + framelen[2] / 8,
							0, 2, BFRAME_POST);
	buf[i] = framelen[2] & 0xff;
	buf[i + 1] = framelen[2] >> 8;
	i += 1432;
	framelen[3] = mpeg1_frame_header(go, buf + i, 0, 1, BFRAME_BIDIR);
	if (go->interlace_coding)
		framelen[3] += mpeg1_frame_header(go, buf + i + framelen[3] / 8,
							0, 2, BFRAME_BIDIR);
	buf[i] = framelen[3] & 0xff;
	buf[i + 1] = framelen[3] >> 8;
	i += 1632 + 16;
	mpeg1_sequence_header(go, buf + i, 0);
	i += 40;
	for (i = 0; i < 5120; i += chunk * 2) {
		if (space - off < 32) {
			off = -1;
			goto done;
		}

		code[off + 1] = __cpu_to_le16(0x8000 | mem);

		chunk = 28;
		if (mem + chunk > 0x4000)
			chunk = 0x4000 - mem;
		if (i + 2 * chunk > 5120)
			chunk = (5120 - i) / 2;

		if (chunk < 28) {
			code[off] = __cpu_to_le16(0x4000 | chunk);
			code[off + 31] = __cpu_to_le16(addr);
			if (mem + chunk == 0x4000) {
				mem = 0x3e00;
				++addr;
			}
		} else {
			code[off] = __cpu_to_le16(0x1000 | 28);
			code[off + 31] = 0;
			mem += 28;
		}

		memcpy(&code[off + 2], buf + i, chunk * 2);
		off += 32;
	}
done:
	kfree(buf);
	return off;
}