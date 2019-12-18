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
struct vl6180_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  VL6180_HOLD ; 
 int /*<<< orphan*/  VL6180_HOLD_ON ; 
 int vl6180_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vl6180_hold(struct vl6180_data *data, bool hold)
{
	return vl6180_write_byte(data->client, VL6180_HOLD,
		hold ? VL6180_HOLD_ON : 0);
}