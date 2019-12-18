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
typedef  int u8 ;
struct rave_sp {int /*<<< orphan*/  serdev; TYPE_1__* variant; } ;
typedef  int /*<<< orphan*/  frame ;
typedef  int /*<<< orphan*/  crc ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/  (* subroutine ) (int const*,int,unsigned char*) ;} ;
struct TYPE_3__ {TYPE_2__* checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HZ ; 
 int RAVE_SP_CHECKSUM_SIZE ; 
 int /*<<< orphan*/  RAVE_SP_ETX ; 
 int /*<<< orphan*/  RAVE_SP_STX ; 
 int RAVE_SP_TX_BUFFER_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,unsigned char*,size_t,int) ; 
 int serdev_device_write (int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int const*,int,unsigned char*) ; 
 unsigned char* stuff (unsigned char*,...) ; 

__attribute__((used)) static int rave_sp_write(struct rave_sp *sp, const u8 *data, u8 data_size)
{
	const size_t checksum_length = sp->variant->checksum->length;
	unsigned char frame[RAVE_SP_TX_BUFFER_SIZE];
	unsigned char crc[RAVE_SP_CHECKSUM_SIZE];
	unsigned char *dest = frame;
	size_t length;

	if (WARN_ON(checksum_length > sizeof(crc)))
		return -ENOMEM;

	if (WARN_ON(data_size > sizeof(frame)))
		return -ENOMEM;

	sp->variant->checksum->subroutine(data, data_size, crc);

	*dest++ = RAVE_SP_STX;
	dest = stuff(dest, data, data_size);
	dest = stuff(dest, crc, checksum_length);
	*dest++ = RAVE_SP_ETX;

	length = dest - frame;

	print_hex_dump_debug("rave-sp tx: ", DUMP_PREFIX_NONE,
			     16, 1, frame, length, false);

	return serdev_device_write(sp->serdev, frame, length, HZ);
}