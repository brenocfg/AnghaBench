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
typedef  int /*<<< orphan*/  u64 ;
struct zpci_dev {int /*<<< orphan*/  fh; } ;
struct ism_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZPCI_CREATE_REQ (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  __zpci_load (void*,int /*<<< orphan*/ ,unsigned long) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __ism_read_cmd(struct ism_dev *ism, void *data,
				  unsigned long offset, unsigned long len)
{
	struct zpci_dev *zdev = to_zpci(ism->pdev);
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 2, 8);

	while (len > 0) {
		__zpci_load(data, req, offset);
		offset += 8;
		data += 8;
		len -= 8;
	}
}