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
struct chtls_dev {int /*<<< orphan*/  tlsdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  tls_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chtls_unregister_dev(struct chtls_dev *cdev)
{
	tls_unregister_device(&cdev->tlsdev);
}