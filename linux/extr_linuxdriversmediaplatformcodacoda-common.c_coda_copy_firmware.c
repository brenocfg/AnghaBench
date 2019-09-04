#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  int u32 ;
struct TYPE_4__ {int* vaddr; } ;
struct coda_dev {TYPE_2__ codebuf; TYPE_1__* devtype; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ CODA_DX6 ; 
 int __le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 

__attribute__((used)) static void coda_copy_firmware(struct coda_dev *dev, const u8 * const buf,
			       size_t size)
{
	u32 *src = (u32 *)buf;

	/* Check if the firmware has a 16-byte Freescale header, skip it */
	if (buf[0] == 'M' && buf[1] == 'X')
		src += 4;
	/*
	 * Check whether the firmware is in native order or pre-reordered for
	 * memory access. The first instruction opcode always is 0xe40e.
	 */
	if (__le16_to_cpup((__le16 *)src) == 0xe40e) {
		u32 *dst = dev->codebuf.vaddr;
		int i;

		/* Firmware in native order, reorder while copying */
		if (dev->devtype->product == CODA_DX6) {
			for (i = 0; i < (size - 16) / 4; i++)
				dst[i] = (src[i] << 16) | (src[i] >> 16);
		} else {
			for (i = 0; i < (size - 16) / 4; i += 2) {
				dst[i] = (src[i + 1] << 16) | (src[i + 1] >> 16);
				dst[i + 1] = (src[i] << 16) | (src[i] >> 16);
			}
		}
	} else {
		/* Copy the already reordered firmware image */
		memcpy(dev->codebuf.vaddr, src, size);
	}
}