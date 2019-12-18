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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ EC_HOST_CMD_REGION0 ; 
 int /*<<< orphan*/  MEC_IO_READ ; 
 int /*<<< orphan*/  cros_ec_lpc_io_bytes_mec (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ *) ; 
 int cros_ec_lpc_mec_in_range (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cros_ec_lpc_read_bytes (unsigned int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 cros_ec_lpc_mec_read_bytes(unsigned int offset, unsigned int length,
				     u8 *dest)
{
	int in_range = cros_ec_lpc_mec_in_range(offset, length);

	if (in_range < 0)
		return 0;

	return in_range ?
		cros_ec_lpc_io_bytes_mec(MEC_IO_READ,
					 offset - EC_HOST_CMD_REGION0,
					 length, dest) :
		cros_ec_lpc_read_bytes(offset, length, dest);
}