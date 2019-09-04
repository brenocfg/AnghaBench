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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct blinkm_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * args; int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  script_startline; int /*<<< orphan*/  script_repeats; int /*<<< orphan*/  script_id; int /*<<< orphan*/  next_brightness; int /*<<< orphan*/  brightness; int /*<<< orphan*/  next_saturation; int /*<<< orphan*/  saturation; int /*<<< orphan*/  next_hue; int /*<<< orphan*/  hue; int /*<<< orphan*/  next_blue; int /*<<< orphan*/  next_green; int /*<<< orphan*/  next_red; } ;

/* Variables and functions */
#define  BLM_FADE_HSB 144 
#define  BLM_FADE_RAND_HSB 143 
#define  BLM_FADE_RAND_RGB 142 
#define  BLM_FADE_RGB 141 
#define  BLM_GET_ADDR 140 
#define  BLM_GET_CUR_RGB 139 
#define  BLM_GET_FW_VER 138 
#define  BLM_GO_RGB 137 
#define  BLM_PLAY_SCRIPT 136 
#define  BLM_READ_SCRIPT_LINE 135 
#define  BLM_SET_ADDR 134 
#define  BLM_SET_FADE_SPEED 133 
#define  BLM_SET_SCRIPT_LR 132 
#define  BLM_SET_STARTUP_PARAM 131 
#define  BLM_SET_TIME_ADJ 130 
#define  BLM_STOP_SCRIPT 129 
#define  BLM_WRITE_SCRIPT_LINE 128 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  blinkm_read (struct i2c_client*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blinkm_write (struct i2c_client*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct blinkm_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int blinkm_transfer_hw(struct i2c_client *client, int cmd)
{
	/* the protocol is simple but non-standard:
	 * e.g.  cmd 'g' (= 0x67) for "get device address"
	 * - which defaults to 0x09 - would be the sequence:
	 *   a) write 0x67 to the device (byte write)
	 *   b) read the value (0x09) back right after (byte read)
	 *
	 * Watch out for "unfinished" sequences (i.e. not enough reads
	 * or writes after a command. It will make the blinkM misbehave.
	 * Sequence is key here.
	 */

	/* args / return are in private data struct */
	struct blinkm_data *data = i2c_get_clientdata(client);

	/* We start hardware transfers which are not to be
	 * mixed with other commands. Aquire a lock now. */
	if (mutex_lock_interruptible(&data->update_lock) < 0)
		return -EAGAIN;

	/* switch cmd - usually write before reads */
	switch (cmd) {
	case BLM_FADE_RAND_RGB:
	case BLM_GO_RGB:
	case BLM_FADE_RGB:
		data->args[0] = data->next_red;
		data->args[1] = data->next_green;
		data->args[2] = data->next_blue;
		blinkm_write(client, cmd, data->args);
		data->red = data->args[0];
		data->green = data->args[1];
		data->blue = data->args[2];
		break;
	case BLM_FADE_HSB:
	case BLM_FADE_RAND_HSB:
		data->args[0] = data->next_hue;
		data->args[1] = data->next_saturation;
		data->args[2] = data->next_brightness;
		blinkm_write(client, cmd, data->args);
		data->hue = data->next_hue;
		data->saturation = data->next_saturation;
		data->brightness = data->next_brightness;
		break;
	case BLM_PLAY_SCRIPT:
		data->args[0] = data->script_id;
		data->args[1] = data->script_repeats;
		data->args[2] = data->script_startline;
		blinkm_write(client, cmd, data->args);
		break;
	case BLM_STOP_SCRIPT:
		blinkm_write(client, cmd, NULL);
		break;
	case BLM_GET_CUR_RGB:
		data->args[0] = data->red;
		data->args[1] = data->green;
		data->args[2] = data->blue;
		blinkm_write(client, cmd, NULL);
		blinkm_read(client, cmd, data->args);
		data->red = data->args[0];
		data->green = data->args[1];
		data->blue = data->args[2];
		break;
	case BLM_GET_ADDR:
		data->args[0] = data->i2c_addr;
		blinkm_write(client, cmd, NULL);
		blinkm_read(client, cmd, data->args);
		data->i2c_addr = data->args[0];
		break;
	case BLM_SET_TIME_ADJ:
	case BLM_SET_FADE_SPEED:
	case BLM_READ_SCRIPT_LINE:
	case BLM_WRITE_SCRIPT_LINE:
	case BLM_SET_SCRIPT_LR:
	case BLM_SET_ADDR:
	case BLM_GET_FW_VER:
	case BLM_SET_STARTUP_PARAM:
		dev_err(&client->dev,
				"BlinkM: cmd %d not implemented yet.\n", cmd);
		break;
	default:
		dev_err(&client->dev, "BlinkM: unknown command %d\n", cmd);
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}			/* end switch(cmd) */

	/* transfers done, unlock */
	mutex_unlock(&data->update_lock);
	return 0;
}