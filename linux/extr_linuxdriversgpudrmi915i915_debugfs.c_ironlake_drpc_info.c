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
typedef  int u16 ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRSTANDVID ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int I915_READ16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMMODECTL ; 
 int MEMMODE_BOOST_EN ; 
 int MEMMODE_BOOST_FREQ_MASK ; 
 int MEMMODE_BOOST_FREQ_SHIFT ; 
 int MEMMODE_FMAX_MASK ; 
 int MEMMODE_FMAX_SHIFT ; 
 int MEMMODE_FMIN_MASK ; 
 int MEMMODE_FSTART_MASK ; 
 int MEMMODE_FSTART_SHIFT ; 
 int MEMMODE_HWIDLE_EN ; 
 int MEMMODE_RCLK_GATE ; 
 int MEMMODE_SWMODE_EN ; 
 int RCX_SW_EXIT ; 
 int /*<<< orphan*/  RSTDBYCTL ; 
 int RSX_STATUS_MASK ; 
#define  RSX_STATUS_ON 133 
#define  RSX_STATUS_RC1 132 
#define  RSX_STATUS_RC1E 131 
#define  RSX_STATUS_RS1 130 
#define  RSX_STATUS_RS2 129 
#define  RSX_STATUS_RS3 128 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int yesno (int) ; 

__attribute__((used)) static int ironlake_drpc_info(struct seq_file *m)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	u32 rgvmodectl, rstdbyctl;
	u16 crstandvid;

	rgvmodectl = I915_READ(MEMMODECTL);
	rstdbyctl = I915_READ(RSTDBYCTL);
	crstandvid = I915_READ16(CRSTANDVID);

	seq_printf(m, "HD boost: %s\n", yesno(rgvmodectl & MEMMODE_BOOST_EN));
	seq_printf(m, "Boost freq: %d\n",
		   (rgvmodectl & MEMMODE_BOOST_FREQ_MASK) >>
		   MEMMODE_BOOST_FREQ_SHIFT);
	seq_printf(m, "HW control enabled: %s\n",
		   yesno(rgvmodectl & MEMMODE_HWIDLE_EN));
	seq_printf(m, "SW control enabled: %s\n",
		   yesno(rgvmodectl & MEMMODE_SWMODE_EN));
	seq_printf(m, "Gated voltage change: %s\n",
		   yesno(rgvmodectl & MEMMODE_RCLK_GATE));
	seq_printf(m, "Starting frequency: P%d\n",
		   (rgvmodectl & MEMMODE_FSTART_MASK) >> MEMMODE_FSTART_SHIFT);
	seq_printf(m, "Max P-state: P%d\n",
		   (rgvmodectl & MEMMODE_FMAX_MASK) >> MEMMODE_FMAX_SHIFT);
	seq_printf(m, "Min P-state: P%d\n", (rgvmodectl & MEMMODE_FMIN_MASK));
	seq_printf(m, "RS1 VID: %d\n", (crstandvid & 0x3f));
	seq_printf(m, "RS2 VID: %d\n", ((crstandvid >> 8) & 0x3f));
	seq_printf(m, "Render standby enabled: %s\n",
		   yesno(!(rstdbyctl & RCX_SW_EXIT)));
	seq_puts(m, "Current RS state: ");
	switch (rstdbyctl & RSX_STATUS_MASK) {
	case RSX_STATUS_ON:
		seq_puts(m, "on\n");
		break;
	case RSX_STATUS_RC1:
		seq_puts(m, "RC1\n");
		break;
	case RSX_STATUS_RC1E:
		seq_puts(m, "RC1E\n");
		break;
	case RSX_STATUS_RS1:
		seq_puts(m, "RS1\n");
		break;
	case RSX_STATUS_RS2:
		seq_puts(m, "RS2 (RC6)\n");
		break;
	case RSX_STATUS_RS3:
		seq_puts(m, "RC3 (RC6+)\n");
		break;
	default:
		seq_puts(m, "unknown\n");
		break;
	}

	return 0;
}