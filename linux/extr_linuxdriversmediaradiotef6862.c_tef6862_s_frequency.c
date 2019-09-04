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
typedef  int u8 ;
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_frequency {unsigned int frequency; scalar_t__ tuner; } ;
struct tef6862_state {unsigned int freq; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  i2cmsg ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned int FREQ_MUL ; 
 int MSA_MODE_PRESET ; 
 int MSA_MODE_SHIFT ; 
 int /*<<< orphan*/  TEF6862_HI_FREQ ; 
 unsigned int TEF6862_LO_FREQ ; 
 int WM_SUB_PLLM ; 
 unsigned int clamp (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 struct tef6862_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tef6862_s_frequency(struct v4l2_subdev *sd, const struct v4l2_frequency *f)
{
	struct tef6862_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	unsigned freq = f->frequency;
	u16 pll;
	u8 i2cmsg[3];
	int err;

	if (f->tuner != 0)
		return -EINVAL;

	freq = clamp(freq, TEF6862_LO_FREQ, TEF6862_HI_FREQ);
	pll = 1964 + ((freq - TEF6862_LO_FREQ) * 20) / FREQ_MUL;
	i2cmsg[0] = (MSA_MODE_PRESET << MSA_MODE_SHIFT) | WM_SUB_PLLM;
	i2cmsg[1] = (pll >> 8) & 0xff;
	i2cmsg[2] = pll & 0xff;

	err = i2c_master_send(client, i2cmsg, sizeof(i2cmsg));
	if (err != sizeof(i2cmsg))
		return err < 0 ? err : -EIO;

	state->freq = freq;
	return 0;
}