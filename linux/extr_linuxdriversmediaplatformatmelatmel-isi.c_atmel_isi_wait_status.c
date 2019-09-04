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
struct atmel_isi {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ISI_CTRL ; 
 int /*<<< orphan*/  ISI_CTRL_DIS ; 
 int /*<<< orphan*/  ISI_CTRL_SRST ; 
 int /*<<< orphan*/  ISI_INTEN ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isi_writel (struct atmel_isi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_isi_wait_status(struct atmel_isi *isi, int wait_reset)
{
	unsigned long timeout;
	/*
	 * The reset or disable will only succeed if we have a
	 * pixel clock from the camera.
	 */
	init_completion(&isi->complete);

	if (wait_reset) {
		isi_writel(isi, ISI_INTEN, ISI_CTRL_SRST);
		isi_writel(isi, ISI_CTRL, ISI_CTRL_SRST);
	} else {
		isi_writel(isi, ISI_INTEN, ISI_CTRL_DIS);
		isi_writel(isi, ISI_CTRL, ISI_CTRL_DIS);
	}

	timeout = wait_for_completion_timeout(&isi->complete,
			msecs_to_jiffies(500));
	if (timeout == 0)
		return -ETIMEDOUT;

	return 0;
}