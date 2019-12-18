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
typedef  int u16 ;
struct dvb_frontend {struct dib0090_fw_state* tuner_priv; } ;
struct dib0090_identity {int p1g; int in_soc; int version; int product; } ;
struct dib0090_fw_state {struct dib0090_identity identity; } ;

/* Variables and functions */
 int EIO ; 
 int KROSUS ; 
 int KROSUS_PLL_LOCKED ; 
#define  MP001 140 
#define  MP005 139 
#define  MP008 138 
#define  MP009 137 
#define  P1A_B 136 
#define  P1C 135 
#define  P1D_E_F 134 
#define  P1G 133 
#define  P1G_21R2 132 
 int SOC ; 
#define  SOC_7090_P1G_11R1 131 
#define  SOC_7090_P1G_21R1 130 
#define  SOC_8090_P1G_11R1 129 
#define  SOC_8090_P1G_21R1 128 
 int dib0090_fw_read_reg (struct dib0090_fw_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static int dib0090_fw_identify(struct dvb_frontend *fe)
{
	struct dib0090_fw_state *state = fe->tuner_priv;
	struct dib0090_identity *identity = &state->identity;

	u16 v = dib0090_fw_read_reg(state, 0x1a);
	identity->p1g = 0;
	identity->in_soc = 0;

	dprintk("FE: Tuner identification (Version = 0x%04x)\n", v);

	/* without PLL lock info */
	v &= ~KROSUS_PLL_LOCKED;

	identity->version = v & 0xff;
	identity->product = (v >> 8) & 0xf;

	if (identity->product != KROSUS)
		goto identification_error;

	if ((identity->version & 0x3) == SOC) {
		identity->in_soc = 1;
		switch (identity->version) {
		case SOC_8090_P1G_11R1:
			dprintk("SOC 8090 P1-G11R1 Has been detected\n");
			identity->p1g = 1;
			break;
		case SOC_8090_P1G_21R1:
			dprintk("SOC 8090 P1-G21R1 Has been detected\n");
			identity->p1g = 1;
			break;
		case SOC_7090_P1G_11R1:
			dprintk("SOC 7090 P1-G11R1 Has been detected\n");
			identity->p1g = 1;
			break;
		case SOC_7090_P1G_21R1:
			dprintk("SOC 7090 P1-G21R1 Has been detected\n");
			identity->p1g = 1;
			break;
		default:
			goto identification_error;
		}
	} else {
		switch ((identity->version >> 5) & 0x7) {
		case MP001:
			dprintk("MP001 : 9090/8096\n");
			break;
		case MP005:
			dprintk("MP005 : Single Sband\n");
			break;
		case MP008:
			dprintk("MP008 : diversity VHF-UHF-LBAND\n");
			break;
		case MP009:
			dprintk("MP009 : diversity 29098 CBAND-UHF-LBAND-SBAND\n");
			break;
		default:
			goto identification_error;
		}

		switch (identity->version & 0x1f) {
		case P1G_21R2:
			dprintk("P1G_21R2 detected\n");
			identity->p1g = 1;
			break;
		case P1G:
			dprintk("P1G detected\n");
			identity->p1g = 1;
			break;
		case P1D_E_F:
			dprintk("P1D/E/F detected\n");
			break;
		case P1C:
			dprintk("P1C detected\n");
			break;
		case P1A_B:
			dprintk("P1-A/B detected: driver is deactivated - not available\n");
			goto identification_error;
			break;
		default:
			goto identification_error;
		}
	}

	return 0;

identification_error:
	return -EIO;
}