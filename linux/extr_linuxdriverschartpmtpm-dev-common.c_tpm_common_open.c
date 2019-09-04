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
struct tpm_chip {int dummy; } ;
struct file_priv {int /*<<< orphan*/  work; int /*<<< orphan*/  user_read_timer; int /*<<< orphan*/  buffer_mutex; struct tpm_chip* chip; } ;
struct file {struct file_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_work ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_reader_timeout ; 

void tpm_common_open(struct file *file, struct tpm_chip *chip,
		     struct file_priv *priv)
{
	priv->chip = chip;
	mutex_init(&priv->buffer_mutex);
	timer_setup(&priv->user_read_timer, user_reader_timeout, 0);
	INIT_WORK(&priv->work, timeout_work);

	file->private_data = priv;
}