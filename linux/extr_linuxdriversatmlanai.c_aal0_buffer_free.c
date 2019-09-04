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
struct lanai_dev {int /*<<< orphan*/  pci; int /*<<< orphan*/  aal0buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  lanai_buf_deallocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aal0_buffer_free(struct lanai_dev *lanai)
{
	DPRINTK("aal0_buffer_allocate: freeing AAL0 RX buffer\n");
	lanai_buf_deallocate(&lanai->aal0buf, lanai->pci);
}