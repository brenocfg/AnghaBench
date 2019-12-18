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
struct i2c_client {int dummy; } ;
struct cx25840_state {int dummy; } ;

/* Variables and functions */
 char const* CX231xx_FIRMWARE ; 
 char const* CX2388x_FIRMWARE ; 
 char const* CX25840_FIRMWARE ; 
 char const* firmware ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ is_cx231xx (struct cx25840_state*) ; 
 scalar_t__ is_cx2388x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *get_fw_name(struct i2c_client *client)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));

	if (firmware[0])
		return firmware;
	if (is_cx2388x(state))
		return CX2388x_FIRMWARE;
	if (is_cx231xx(state))
		return CX231xx_FIRMWARE;
	return CX25840_FIRMWARE;
}