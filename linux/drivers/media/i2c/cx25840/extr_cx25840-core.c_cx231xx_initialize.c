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
struct workqueue_struct {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int /*<<< orphan*/  aud_input; int /*<<< orphan*/  vid_input; int /*<<< orphan*/  fw_wait; int /*<<< orphan*/  fw_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 struct workqueue_struct* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  cx25840_std_setup (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25840_work_handler ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (struct workqueue_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_input (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void cx231xx_initialize(struct i2c_client *client)
{
	DEFINE_WAIT(wait);
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	struct workqueue_struct *q;

	/* Internal Reset */
	cx25840_and_or(client, 0x102, ~0x01, 0x01);
	cx25840_and_or(client, 0x102, ~0x01, 0x00);

	/* Stop microcontroller */
	cx25840_and_or(client, 0x803, ~0x10, 0x00);

	/* DIF in reset? */
	cx25840_write(client, 0x398, 0);

	/* Trust the default xtal, no division */
	/* This changes for the cx23888 products */
	cx25840_write(client, 0x2, 0x76);

	/* Bring down the regulator for AUX clk */
	cx25840_write(client, 0x1, 0x40);

	/* Disable DIF bypass */
	cx25840_write4(client, 0x33c, 0x00000001);

	/* DIF Src phase inc */
	cx25840_write4(client, 0x340, 0x0df7df83);

	/* Luma */
	cx25840_write4(client, 0x414, 0x00107d12);

	/* Chroma */
	cx25840_write4(client, 0x420, 0x3d008282);

	/* ADC2 input select */
	cx25840_write(client, 0x102, 0x10);

	/* VIN1 & VIN5 */
	cx25840_write(client, 0x103, 0x11);

	/* Enable format auto detect */
	cx25840_write(client, 0x400, 0);
	/* Fast subchroma lock */
	/* White crush, Chroma AGC & Chroma Killer enabled */
	cx25840_write(client, 0x401, 0xe8);

	/*
	 * Do the firmware load in a work handler to prevent.
	 * Otherwise the kernel is blocked waiting for the
	 * bit-banging i2c interface to finish uploading the
	 * firmware.
	 */
	INIT_WORK(&state->fw_work, cx25840_work_handler);
	init_waitqueue_head(&state->fw_wait);
	q = create_singlethread_workqueue("cx25840_fw");
	if (q) {
		prepare_to_wait(&state->fw_wait, &wait, TASK_UNINTERRUPTIBLE);
		queue_work(q, &state->fw_work);
		schedule();
		finish_wait(&state->fw_wait, &wait);
		destroy_workqueue(q);
	}

	cx25840_std_setup(client);

	/* (re)set input */
	set_input(client, state->vid_input, state->aud_input);

	/* start microcontroller */
	cx25840_and_or(client, 0x803, ~0x10, 0x10);

	/* CC raw enable */
	cx25840_write(client, 0x404, 0x0b);

	/* CC on */
	cx25840_write(client, 0x42f, 0x66);
	cx25840_write4(client, 0x474, 0x1e1e601a);
}