#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_2__ {int base; int ngpio; } ;
struct npcm7xx_gpio {scalar_t__ base; TYPE_1__ gc; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ NPCM7XX_GP_N_DBNC ; 
 scalar_t__ NPCM7XX_GP_N_DIN ; 
 scalar_t__ NPCM7XX_GP_N_DOUT ; 
 scalar_t__ NPCM7XX_GP_N_EVBE ; 
 scalar_t__ NPCM7XX_GP_N_EVEN ; 
 scalar_t__ NPCM7XX_GP_N_EVST ; 
 scalar_t__ NPCM7XX_GP_N_EVTYP ; 
 scalar_t__ NPCM7XX_GP_N_IEM ; 
 scalar_t__ NPCM7XX_GP_N_MPLCK ; 
 scalar_t__ NPCM7XX_GP_N_OBL0 ; 
 scalar_t__ NPCM7XX_GP_N_OBL1 ; 
 scalar_t__ NPCM7XX_GP_N_OBL2 ; 
 scalar_t__ NPCM7XX_GP_N_OBL3 ; 
 scalar_t__ NPCM7XX_GP_N_ODSC ; 
 scalar_t__ NPCM7XX_GP_N_OE ; 
 scalar_t__ NPCM7XX_GP_N_OSRC ; 
 scalar_t__ NPCM7XX_GP_N_OTYP ; 
 scalar_t__ NPCM7XX_GP_N_PD ; 
 scalar_t__ NPCM7XX_GP_N_POL ; 
 scalar_t__ NPCM7XX_GP_N_PU ; 
 scalar_t__ NPCM7XX_GP_N_SPLCK ; 
 struct npcm7xx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,...) ; 

__attribute__((used)) static void npcmgpio_dbg_show(struct seq_file *s, struct gpio_chip *chip)
{
	struct npcm7xx_gpio *bank = gpiochip_get_data(chip);

	seq_printf(s, "-- module %d [gpio%d - %d]\n",
		   bank->gc.base / bank->gc.ngpio,
		   bank->gc.base,
		   bank->gc.base + bank->gc.ngpio);
	seq_printf(s, "DIN :%.8x DOUT:%.8x IE  :%.8x OE	 :%.8x\n",
		   ioread32(bank->base + NPCM7XX_GP_N_DIN),
		   ioread32(bank->base + NPCM7XX_GP_N_DOUT),
		   ioread32(bank->base + NPCM7XX_GP_N_IEM),
		   ioread32(bank->base + NPCM7XX_GP_N_OE));
	seq_printf(s, "PU  :%.8x PD  :%.8x DB  :%.8x POL :%.8x\n",
		   ioread32(bank->base + NPCM7XX_GP_N_PU),
		   ioread32(bank->base + NPCM7XX_GP_N_PD),
		   ioread32(bank->base + NPCM7XX_GP_N_DBNC),
		   ioread32(bank->base + NPCM7XX_GP_N_POL));
	seq_printf(s, "ETYP:%.8x EVBE:%.8x EVEN:%.8x EVST:%.8x\n",
		   ioread32(bank->base + NPCM7XX_GP_N_EVTYP),
		   ioread32(bank->base + NPCM7XX_GP_N_EVBE),
		   ioread32(bank->base + NPCM7XX_GP_N_EVEN),
		   ioread32(bank->base + NPCM7XX_GP_N_EVST));
	seq_printf(s, "OTYP:%.8x OSRC:%.8x ODSC:%.8x\n",
		   ioread32(bank->base + NPCM7XX_GP_N_OTYP),
		   ioread32(bank->base + NPCM7XX_GP_N_OSRC),
		   ioread32(bank->base + NPCM7XX_GP_N_ODSC));
	seq_printf(s, "OBL0:%.8x OBL1:%.8x OBL2:%.8x OBL3:%.8x\n",
		   ioread32(bank->base + NPCM7XX_GP_N_OBL0),
		   ioread32(bank->base + NPCM7XX_GP_N_OBL1),
		   ioread32(bank->base + NPCM7XX_GP_N_OBL2),
		   ioread32(bank->base + NPCM7XX_GP_N_OBL3));
	seq_printf(s, "SLCK:%.8x MLCK:%.8x\n",
		   ioread32(bank->base + NPCM7XX_GP_N_SPLCK),
		   ioread32(bank->base + NPCM7XX_GP_N_MPLCK));
}