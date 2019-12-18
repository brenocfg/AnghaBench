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
struct comedi_insn {int n; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_DEVICE_CONFIG_CONNECT_ROUTE 131 
#define  INSN_DEVICE_CONFIG_DISCONNECT_ROUTE 130 
#define  INSN_DEVICE_CONFIG_GET_ROUTES 129 
#define  INSN_DEVICE_CONFIG_TEST_ROUTE 128 

__attribute__((used)) static int check_insn_device_config_length(struct comedi_insn *insn,
					   unsigned int *data)
{
	if (insn->n < 1)
		return -EINVAL;

	switch (data[0]) {
	case INSN_DEVICE_CONFIG_TEST_ROUTE:
	case INSN_DEVICE_CONFIG_CONNECT_ROUTE:
	case INSN_DEVICE_CONFIG_DISCONNECT_ROUTE:
		if (insn->n == 3)
			return 0;
		break;
	case INSN_DEVICE_CONFIG_GET_ROUTES:
		/*
		 * Big enough for config_id and the length of the userland
		 * memory buffer.  Additional length should be in factors of 2
		 * to communicate any returned route pairs (source,destination).
		 */
		if (insn->n >= 2)
			return 0;
		break;
	}
	return -EINVAL;
}