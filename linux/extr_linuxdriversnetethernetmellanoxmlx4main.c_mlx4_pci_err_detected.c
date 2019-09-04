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
struct pci_dev {int dummy; } ;
struct mlx4_dev_persistent {int interface_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  interface_state_mutex; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int MLX4_INTERFACE_STATE_UP ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  mlx4_enter_error_state (struct mlx4_dev_persistent*) ; 
 int /*<<< orphan*/  mlx4_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlx4_pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_unload_one (struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 struct mlx4_dev_persistent* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t mlx4_pci_err_detected(struct pci_dev *pdev,
					      pci_channel_state_t state)
{
	struct mlx4_dev_persistent *persist = pci_get_drvdata(pdev);

	mlx4_err(persist->dev, "mlx4_pci_err_detected was called\n");
	mlx4_enter_error_state(persist);

	mutex_lock(&persist->interface_state_mutex);
	if (persist->interface_state & MLX4_INTERFACE_STATE_UP)
		mlx4_unload_one(pdev);

	mutex_unlock(&persist->interface_state_mutex);
	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	mlx4_pci_disable_device(persist->dev);
	return PCI_ERS_RESULT_NEED_RESET;
}