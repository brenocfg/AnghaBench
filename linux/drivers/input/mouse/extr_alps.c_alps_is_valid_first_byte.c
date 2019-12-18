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
struct alps_data {unsigned char mask0; unsigned char byte0; } ;

/* Variables and functions */

__attribute__((used)) static bool alps_is_valid_first_byte(struct alps_data *priv,
				     unsigned char data)
{
	return (data & priv->mask0) == priv->byte0;
}