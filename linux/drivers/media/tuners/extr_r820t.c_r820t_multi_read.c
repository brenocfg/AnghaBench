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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct r820t_priv {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int r820t_read (struct r820t_priv*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int r820t_multi_read(struct r820t_priv *priv)
{
	int rc, i;
	u16 sum = 0;
	u8 data[2], min = 255, max = 0;

	usleep_range(5000, 6000);

	for (i = 0; i < 6; i++) {
		rc = r820t_read(priv, 0x00, data, sizeof(data));
		if (rc < 0)
			return rc;

		sum += data[1];

		if (data[1] < min)
			min = data[1];

		if (data[1] > max)
			max = data[1];
	}
	rc = sum - max - min;

	return rc;
}