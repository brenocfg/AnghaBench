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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct hci_dev {int dummy; } ;
typedef  enum qca_btsoc_type { ____Placeholder_qca_btsoc_type } qca_btsoc_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int qca_uart_setup(struct hci_dev *hdev, uint8_t baudrate,
				 enum qca_btsoc_type soc_type, u32 soc_ver)
{
	return -EOPNOTSUPP;
}