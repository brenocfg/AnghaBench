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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct inno_hdmi {int dummy; } ;

/* Variables and functions */
 int hdmi_readb (struct inno_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hdmi_modb(struct inno_hdmi *hdmi, u16 offset,
			     u32 msk, u32 val)
{
	u8 temp = hdmi_readb(hdmi, offset) & ~msk;

	temp |= val & msk;
	hdmi_writeb(hdmi, offset, temp);
}