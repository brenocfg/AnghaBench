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
struct zd_rf {int dummy; } ;
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  const member_0; } ;
struct zd_chip {scalar_t__ new_phy_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
#define  ZD_CR10 203 
#define  ZD_CR100 202 
#define  ZD_CR101 201 
#define  ZD_CR102 200 
#define  ZD_CR106 199 
#define  ZD_CR107 198 
#define  ZD_CR109 197 
#define  ZD_CR110 196 
#define  ZD_CR111 195 
#define  ZD_CR112 194 
#define  ZD_CR113 193 
#define  ZD_CR114 192 
#define  ZD_CR115 191 
#define  ZD_CR116 190 
#define  ZD_CR117 189 
#define  ZD_CR118 188 
#define  ZD_CR119 187 
#define  ZD_CR120 186 
#define  ZD_CR121 185 
#define  ZD_CR122 184 
#define  ZD_CR123 183 
#define  ZD_CR125 182 
#define  ZD_CR126 181 
#define  ZD_CR127 180 
#define  ZD_CR128 179 
#define  ZD_CR129 178 
#define  ZD_CR130 177 
#define  ZD_CR131 176 
#define  ZD_CR136 175 
#define  ZD_CR137 174 
#define  ZD_CR138 173 
#define  ZD_CR144 172 
#define  ZD_CR148 171 
#define  ZD_CR149 170 
#define  ZD_CR15 169 
#define  ZD_CR150 168 
#define  ZD_CR17 167 
#define  ZD_CR20 166 
#define  ZD_CR23 165 
#define  ZD_CR24 164 
#define  ZD_CR240 163 
#define  ZD_CR251 162 
#define  ZD_CR252 161 
#define  ZD_CR253 160 
#define  ZD_CR26 159 
#define  ZD_CR28 158 
#define  ZD_CR29 157 
#define  ZD_CR33 156 
#define  ZD_CR34 155 
#define  ZD_CR35 154 
#define  ZD_CR38 153 
#define  ZD_CR41 152 
#define  ZD_CR44 151 
#define  ZD_CR46 150 
#define  ZD_CR47 149 
#define  ZD_CR48 148 
#define  ZD_CR49 147 
#define  ZD_CR51 146 
#define  ZD_CR52 145 
#define  ZD_CR53 144 
#define  ZD_CR65 143 
#define  ZD_CR66 142 
#define  ZD_CR67 141 
#define  ZD_CR68 140 
#define  ZD_CR69 139 
#define  ZD_CR79 138 
#define  ZD_CR80 137 
#define  ZD_CR81 136 
#define  ZD_CR87 135 
#define  ZD_CR89 134 
#define  ZD_CR9 133 
#define  ZD_CR90 132 
#define  ZD_CR91 131 
#define  ZD_CR92 130 
#define  ZD_CR98 129 
#define  ZD_CR99 128 
 struct zd_ioreq16 const** chan_rv ; 
 struct zd_ioreq16 const* rv_init1 ; 
 struct zd_ioreq16 const* rv_init2 ; 
 struct zd_ioreq16 const* std_rv ; 
 int zd1211b_al7230b_finalize (struct zd_chip*) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 
 int zd_rfwritev_cr_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1211b_al7230b_init_hw(struct zd_rf *rf)
{
	int r;
	struct zd_chip *chip = zd_rf_to_chip(rf);

	static const struct zd_ioreq16 ioreqs_1[] = {
		{ ZD_CR240, 0x57 }, { ZD_CR9,   0x9 },
		{ },
		{ ZD_CR10,  0x8b }, { ZD_CR15,  0x20 },
		{ ZD_CR17,  0x2B }, /* for newest (3rd cut) AL2230 */
		{ ZD_CR20,  0x10 }, /* 4N25->Stone Request */
		{ ZD_CR23,  0x40 }, { ZD_CR24,  0x20 }, { ZD_CR26,  0x93 },
		{ ZD_CR28,  0x3e }, { ZD_CR29,  0x00 },
		{ ZD_CR33,  0x28 }, /* 5613 */
		{ ZD_CR34,  0x30 },
		{ ZD_CR35,  0x3e }, /* for newest (3rd cut) AL2230 */
		{ ZD_CR41,  0x24 }, { ZD_CR44,  0x32 },
		{ ZD_CR46,  0x99 }, /* for newest (3rd cut) AL2230 */
		{ ZD_CR47,  0x1e },

		/* ZD1215 5610 */
		{ ZD_CR48,  0x00 }, { ZD_CR49,  0x00 }, { ZD_CR51,  0x01 },
		{ ZD_CR52,  0x80 }, { ZD_CR53,  0x7e }, { ZD_CR65,  0x00 },
		{ ZD_CR66,  0x00 }, { ZD_CR67,  0x00 }, { ZD_CR68,  0x00 },
		{ ZD_CR69,  0x28 },

		{ ZD_CR79,  0x58 }, { ZD_CR80,  0x30 }, { ZD_CR81,  0x30 },
		{ ZD_CR87,  0x0A }, { ZD_CR89,  0x04 },
		{ ZD_CR90,  0x58 }, /* 5112 */
		{ ZD_CR91,  0x00 }, /* 5613 */
		{ ZD_CR92,  0x0a },
		{ ZD_CR98,  0x8d }, /* 4804, for 1212 new algorithm */
		{ ZD_CR99,  0x00 }, { ZD_CR100, 0x02 }, { ZD_CR101, 0x13 },
		{ ZD_CR102, 0x27 },
		{ ZD_CR106, 0x20 }, /* change to 0x24 for AL7230B */
		{ ZD_CR109, 0x13 }, /* 4804, for 1212 new algorithm */
		{ ZD_CR112, 0x1f },
	};

	static const struct zd_ioreq16 ioreqs_new_phy[] = {
		{ ZD_CR107, 0x28 },
		{ ZD_CR110, 0x1f }, /* 5127, 0x13->0x1f */
		{ ZD_CR111, 0x1f }, /* 0x13 to 0x1f for AL7230B */
		{ ZD_CR116, 0x2a }, { ZD_CR118, 0xfa }, { ZD_CR119, 0x12 },
		{ ZD_CR121, 0x6c }, /* 5613 */
	};

	static const struct zd_ioreq16 ioreqs_old_phy[] = {
		{ ZD_CR107, 0x24 },
		{ ZD_CR110, 0x13 }, /* 5127, 0x13->0x1f */
		{ ZD_CR111, 0x13 }, /* 0x13 to 0x1f for AL7230B */
		{ ZD_CR116, 0x24 }, { ZD_CR118, 0xfc }, { ZD_CR119, 0x11 },
		{ ZD_CR121, 0x6a }, /* 5613 */
	};

	static const struct zd_ioreq16 ioreqs_2[] = {
		{ ZD_CR113, 0x27 }, { ZD_CR114, 0x27 }, { ZD_CR115, 0x24 },
		{ ZD_CR117, 0xfa }, { ZD_CR120, 0x4f },
		{ ZD_CR122, 0xfc }, /* E0->FCh at 4901 */
		{ ZD_CR123, 0x57 }, /* 5613 */
		{ ZD_CR125, 0xad }, /* 4804, for 1212 new algorithm */
		{ ZD_CR126, 0x6c }, /* 5613 */
		{ ZD_CR127, 0x03 }, /* 4804, for 1212 new algorithm */
		{ ZD_CR130, 0x10 },
		{ ZD_CR131, 0x00 }, /* 5112 */
		{ ZD_CR137, 0x50 }, /* 5613 */
		{ ZD_CR138, 0xa8 }, /* 5112 */
		{ ZD_CR144, 0xac }, /* 5613 */
		{ ZD_CR148, 0x40 }, /* 5112 */
		{ ZD_CR149, 0x40 }, /* 4O07, 50->40 */
		{ ZD_CR150, 0x1a }, /* 5112, 0C->1A */
		{ ZD_CR252, 0x34 }, { ZD_CR253, 0x34 },
		{ ZD_CR251, 0x2f }, /* PLL_OFF */
	};

	static const struct zd_ioreq16 ioreqs_3[] = {
		{ ZD_CR251, 0x7f }, /* PLL_ON */
		{ ZD_CR128, 0x14 }, { ZD_CR129, 0x12 }, { ZD_CR130, 0x10 },
		{ ZD_CR38,  0x38 }, { ZD_CR136, 0xdf },
	};

	r = zd_iowrite16a_locked(chip, ioreqs_1, ARRAY_SIZE(ioreqs_1));
	if (r)
		return r;

	if (chip->new_phy_layout)
		r = zd_iowrite16a_locked(chip, ioreqs_new_phy,
			ARRAY_SIZE(ioreqs_new_phy));
	else
		r = zd_iowrite16a_locked(chip, ioreqs_old_phy,
			ARRAY_SIZE(ioreqs_old_phy));
	if (r)
		return r;

	r = zd_iowrite16a_locked(chip, ioreqs_2, ARRAY_SIZE(ioreqs_2));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, chan_rv[0], ARRAY_SIZE(chan_rv[0]));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, std_rv, ARRAY_SIZE(std_rv));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, rv_init1, ARRAY_SIZE(rv_init1));
	if (r)
		return r;

	r = zd_iowrite16a_locked(chip, ioreqs_3, ARRAY_SIZE(ioreqs_3));
	if (r)
		return r;

	r = zd_rfwritev_cr_locked(chip, rv_init2, ARRAY_SIZE(rv_init2));
	if (r)
		return r;

	return zd1211b_al7230b_finalize(chip);
}