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
typedef  int u32 ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int cx231xx_set_audclk_freq (struct i2c_client*,int) ; 
 int cx23885_set_audclk_freq (struct i2c_client*,int) ; 
 int cx25836_set_audclk_freq (struct i2c_client*,int) ; 
 int cx25840_set_audclk_freq (struct i2c_client*,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ is_cx231xx (struct cx25840_state*) ; 
 scalar_t__ is_cx2388x (struct cx25840_state*) ; 
 scalar_t__ is_cx2583x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_audclk_freq(struct i2c_client *client, u32 freq)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));

	if (freq != 32000 && freq != 44100 && freq != 48000)
		return -EINVAL;

	if (is_cx231xx(state))
		return cx231xx_set_audclk_freq(client, freq);

	if (is_cx2388x(state))
		return cx23885_set_audclk_freq(client, freq);

	if (is_cx2583x(state))
		return cx25836_set_audclk_freq(client, freq);

	return cx25840_set_audclk_freq(client, freq);
}