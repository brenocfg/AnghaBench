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
struct mcam_camera {int dummy; } ;

/* Variables and functions */
 int GFCR_GPIO_ON ; 
 int GGPIO_OUT ; 
 int GPR_C0EN ; 
 int GPR_C1 ; 
 int GPR_C1EN ; 
 int /*<<< orphan*/  REG_GL_FCR ; 
 int /*<<< orphan*/  REG_GL_GPIOR ; 
 int /*<<< orphan*/  REG_GPR ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cafe_ctlr_power_down(struct mcam_camera *mcam)
{
	mcam_reg_write(mcam, REG_GPR, GPR_C1EN|GPR_C0EN|GPR_C1);
	mcam_reg_write(mcam, REG_GL_FCR, GFCR_GPIO_ON);
	mcam_reg_write(mcam, REG_GL_GPIOR, GGPIO_OUT);
}