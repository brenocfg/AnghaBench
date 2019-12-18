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
struct ds1305 {int* ctrl; int /*<<< orphan*/  spi; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int DS1305_AEI0 ; 
 int DS1305_CONTROL ; 
 int DS1305_WRITE ; 
 long EINVAL ; 
 struct ds1305* dev_get_drvdata (struct device*) ; 
 long spi_write_then_read (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds1305_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct ds1305	*ds1305 = dev_get_drvdata(dev);
	u8		buf[2];
	long		err = -EINVAL;

	buf[0] = DS1305_WRITE | DS1305_CONTROL;
	buf[1] = ds1305->ctrl[0];

	if (enabled) {
		if (ds1305->ctrl[0] & DS1305_AEI0)
			goto done;
		buf[1] |= DS1305_AEI0;
	} else {
		if (!(buf[1] & DS1305_AEI0))
			goto done;
		buf[1] &= ~DS1305_AEI0;
	}
	err = spi_write_then_read(ds1305->spi, buf, sizeof(buf), NULL, 0);
	if (err >= 0)
		ds1305->ctrl[0] = buf[1];
done:
	return err;

}