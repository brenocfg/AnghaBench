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
typedef  unsigned int u16 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_AUXDATA_OFF ; 
 int /*<<< orphan*/  HFA384X_AUXOFFSET_OFF ; 
 int /*<<< orphan*/  HFA384X_AUXPAGE_OFF ; 
 int /*<<< orphan*/  HFA384X_OUTSW (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  HFA384X_OUTW (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HFA384X_OUTW_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hfa384x_to_aux(struct net_device *dev, unsigned int addr, int len,
			  void *buf)
{
	u16 page, offset;
	if (addr & 1 || len & 1)
		return -1;

	page = addr >> 7;
	offset = addr & 0x7f;

	HFA384X_OUTW(page, HFA384X_AUXPAGE_OFF);
	HFA384X_OUTW(offset, HFA384X_AUXOFFSET_OFF);

	udelay(5);

#ifdef PRISM2_PCI
	{
		__le16 *pos = (__le16 *) buf;
		while (len > 0) {
			HFA384X_OUTW_DATA(*pos++, HFA384X_AUXDATA_OFF);
			len -= 2;
		}
	}
#else /* PRISM2_PCI */
	HFA384X_OUTSW(HFA384X_AUXDATA_OFF, buf, len / 2);
#endif /* PRISM2_PCI */

	return 0;
}