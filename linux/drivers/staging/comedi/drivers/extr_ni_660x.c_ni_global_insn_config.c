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
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_DEVICE_CONFIG_CONNECT_ROUTE 130 
#define  INSN_DEVICE_CONFIG_DISCONNECT_ROUTE 129 
#define  INSN_DEVICE_CONFIG_TEST_ROUTE 128 
 int connect_route (unsigned int,unsigned int,struct comedi_device*) ; 
 int disconnect_route (unsigned int,unsigned int,struct comedi_device*) ; 
 unsigned int test_route (unsigned int,unsigned int,struct comedi_device*) ; 

__attribute__((used)) static int ni_global_insn_config(struct comedi_device *dev,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	switch (data[0]) {
	case INSN_DEVICE_CONFIG_TEST_ROUTE:
		data[0] = test_route(data[1], data[2], dev);
		return 2;
	case INSN_DEVICE_CONFIG_CONNECT_ROUTE:
		return connect_route(data[1], data[2], dev);
	case INSN_DEVICE_CONFIG_DISCONNECT_ROUTE:
		return disconnect_route(data[1], data[2], dev);
	/*
	 * This case is already handled one level up.
	 * case INSN_DEVICE_CONFIG_GET_ROUTES:
	 */
	default:
		return -EINVAL;
	}
	return 1;
}