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

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  PSCI_RET_DENIED 132 
#define  PSCI_RET_INVALID_ADDRESS 131 
#define  PSCI_RET_INVALID_PARAMS 130 
#define  PSCI_RET_NOT_SUPPORTED 129 
#define  PSCI_RET_SUCCESS 128 

__attribute__((used)) static int psci_to_linux_errno(int errno)
{
	switch (errno) {
	case PSCI_RET_SUCCESS:
		return 0;
	case PSCI_RET_NOT_SUPPORTED:
		return -EOPNOTSUPP;
	case PSCI_RET_INVALID_PARAMS:
	case PSCI_RET_INVALID_ADDRESS:
		return -EINVAL;
	case PSCI_RET_DENIED:
		return -EPERM;
	};

	return -EINVAL;
}