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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int /*<<< orphan*/  DECRYPT ; 
 int /*<<< orphan*/  DES3_SPEED_VECTORS ; 
 int /*<<< orphan*/  ENCRYPT ; 
 int ENOENT ; 
 int /*<<< orphan*/  aead_speed_template_19 ; 
 int /*<<< orphan*/  aead_speed_template_20 ; 
 int /*<<< orphan*/  aead_speed_template_36 ; 
 int /*<<< orphan*/  crypto_has_alg (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * des3_speed_template ; 
 int /*<<< orphan*/  generic_hash_speed_template ; 
 int /*<<< orphan*/  hash_speed_template_16 ; 
 int mode ; 
 int /*<<< orphan*/  poly1305_speed_template ; 
 int /*<<< orphan*/  sec ; 
 int /*<<< orphan*/  speed_template_16_24_32 ; 
 int /*<<< orphan*/  speed_template_16_32 ; 
 int /*<<< orphan*/  speed_template_20_28_36 ; 
 int /*<<< orphan*/  speed_template_24 ; 
 int /*<<< orphan*/  speed_template_32 ; 
 int /*<<< orphan*/  speed_template_32_40_48 ; 
 int /*<<< orphan*/  speed_template_32_48 ; 
 int /*<<< orphan*/  speed_template_32_48_64 ; 
 int /*<<< orphan*/  speed_template_32_64 ; 
 int /*<<< orphan*/  speed_template_8 ; 
 int /*<<< orphan*/  speed_template_8_16 ; 
 int /*<<< orphan*/  speed_template_8_32 ; 
 int tcrypt_test (char*) ; 
 int /*<<< orphan*/  test_acipher_speed (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_aead_speed (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ahash_speed (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_available () ; 
 int /*<<< orphan*/  test_cipher_speed (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_hash_speed (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_mb_aead_speed (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_mb_ahash_speed (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_mb_skcipher_speed (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_test(const char *alg, u32 type, u32 mask, int m, u32 num_mb)
{
	int i;
	int ret = 0;

	switch (m) {
	case 0:
		if (alg) {
			if (!crypto_has_alg(alg, type,
					    mask ?: CRYPTO_ALG_TYPE_MASK))
				ret = -ENOENT;
			break;
		}

		for (i = 1; i < 200; i++)
			ret += do_test(NULL, 0, 0, i, num_mb);
		break;

	case 1:
		ret += tcrypt_test("md5");
		break;

	case 2:
		ret += tcrypt_test("sha1");
		break;

	case 3:
		ret += tcrypt_test("ecb(des)");
		ret += tcrypt_test("cbc(des)");
		ret += tcrypt_test("ctr(des)");
		break;

	case 4:
		ret += tcrypt_test("ecb(des3_ede)");
		ret += tcrypt_test("cbc(des3_ede)");
		ret += tcrypt_test("ctr(des3_ede)");
		break;

	case 5:
		ret += tcrypt_test("md4");
		break;

	case 6:
		ret += tcrypt_test("sha256");
		break;

	case 7:
		ret += tcrypt_test("ecb(blowfish)");
		ret += tcrypt_test("cbc(blowfish)");
		ret += tcrypt_test("ctr(blowfish)");
		break;

	case 8:
		ret += tcrypt_test("ecb(twofish)");
		ret += tcrypt_test("cbc(twofish)");
		ret += tcrypt_test("ctr(twofish)");
		ret += tcrypt_test("lrw(twofish)");
		ret += tcrypt_test("xts(twofish)");
		break;

	case 9:
		ret += tcrypt_test("ecb(serpent)");
		ret += tcrypt_test("cbc(serpent)");
		ret += tcrypt_test("ctr(serpent)");
		ret += tcrypt_test("lrw(serpent)");
		ret += tcrypt_test("xts(serpent)");
		break;

	case 10:
		ret += tcrypt_test("ecb(aes)");
		ret += tcrypt_test("cbc(aes)");
		ret += tcrypt_test("lrw(aes)");
		ret += tcrypt_test("xts(aes)");
		ret += tcrypt_test("ctr(aes)");
		ret += tcrypt_test("rfc3686(ctr(aes))");
		ret += tcrypt_test("cfb(aes)");
		break;

	case 11:
		ret += tcrypt_test("sha384");
		break;

	case 12:
		ret += tcrypt_test("sha512");
		break;

	case 13:
		ret += tcrypt_test("deflate");
		break;

	case 14:
		ret += tcrypt_test("ecb(cast5)");
		ret += tcrypt_test("cbc(cast5)");
		ret += tcrypt_test("ctr(cast5)");
		break;

	case 15:
		ret += tcrypt_test("ecb(cast6)");
		ret += tcrypt_test("cbc(cast6)");
		ret += tcrypt_test("ctr(cast6)");
		ret += tcrypt_test("lrw(cast6)");
		ret += tcrypt_test("xts(cast6)");
		break;

	case 16:
		ret += tcrypt_test("ecb(arc4)");
		break;

	case 17:
		ret += tcrypt_test("michael_mic");
		break;

	case 18:
		ret += tcrypt_test("crc32c");
		break;

	case 19:
		ret += tcrypt_test("ecb(tea)");
		break;

	case 20:
		ret += tcrypt_test("ecb(xtea)");
		break;

	case 21:
		ret += tcrypt_test("ecb(khazad)");
		break;

	case 22:
		ret += tcrypt_test("wp512");
		break;

	case 23:
		ret += tcrypt_test("wp384");
		break;

	case 24:
		ret += tcrypt_test("wp256");
		break;

	case 25:
		ret += tcrypt_test("ecb(tnepres)");
		break;

	case 26:
		ret += tcrypt_test("ecb(anubis)");
		ret += tcrypt_test("cbc(anubis)");
		break;

	case 27:
		ret += tcrypt_test("tgr192");
		break;

	case 28:
		ret += tcrypt_test("tgr160");
		break;

	case 29:
		ret += tcrypt_test("tgr128");
		break;

	case 30:
		ret += tcrypt_test("ecb(xeta)");
		break;

	case 31:
		ret += tcrypt_test("pcbc(fcrypt)");
		break;

	case 32:
		ret += tcrypt_test("ecb(camellia)");
		ret += tcrypt_test("cbc(camellia)");
		ret += tcrypt_test("ctr(camellia)");
		ret += tcrypt_test("lrw(camellia)");
		ret += tcrypt_test("xts(camellia)");
		break;

	case 33:
		ret += tcrypt_test("sha224");
		break;

	case 34:
		ret += tcrypt_test("salsa20");
		break;

	case 35:
		ret += tcrypt_test("gcm(aes)");
		break;

	case 36:
		ret += tcrypt_test("lzo");
		break;

	case 37:
		ret += tcrypt_test("ccm(aes)");
		break;

	case 38:
		ret += tcrypt_test("cts(cbc(aes))");
		break;

        case 39:
		ret += tcrypt_test("rmd128");
		break;

        case 40:
		ret += tcrypt_test("rmd160");
		break;

	case 41:
		ret += tcrypt_test("rmd256");
		break;

	case 42:
		ret += tcrypt_test("rmd320");
		break;

	case 43:
		ret += tcrypt_test("ecb(seed)");
		break;

	case 44:
		ret += tcrypt_test("zlib");
		break;

	case 45:
		ret += tcrypt_test("rfc4309(ccm(aes))");
		break;

	case 46:
		ret += tcrypt_test("ghash");
		break;

	case 47:
		ret += tcrypt_test("crct10dif");
		break;

	case 48:
		ret += tcrypt_test("sha3-224");
		break;

	case 49:
		ret += tcrypt_test("sha3-256");
		break;

	case 50:
		ret += tcrypt_test("sha3-384");
		break;

	case 51:
		ret += tcrypt_test("sha3-512");
		break;

	case 52:
		ret += tcrypt_test("sm3");
		break;

	case 100:
		ret += tcrypt_test("hmac(md5)");
		break;

	case 101:
		ret += tcrypt_test("hmac(sha1)");
		break;

	case 102:
		ret += tcrypt_test("hmac(sha256)");
		break;

	case 103:
		ret += tcrypt_test("hmac(sha384)");
		break;

	case 104:
		ret += tcrypt_test("hmac(sha512)");
		break;

	case 105:
		ret += tcrypt_test("hmac(sha224)");
		break;

	case 106:
		ret += tcrypt_test("xcbc(aes)");
		break;

	case 107:
		ret += tcrypt_test("hmac(rmd128)");
		break;

	case 108:
		ret += tcrypt_test("hmac(rmd160)");
		break;

	case 109:
		ret += tcrypt_test("vmac64(aes)");
		break;

	case 111:
		ret += tcrypt_test("hmac(sha3-224)");
		break;

	case 112:
		ret += tcrypt_test("hmac(sha3-256)");
		break;

	case 113:
		ret += tcrypt_test("hmac(sha3-384)");
		break;

	case 114:
		ret += tcrypt_test("hmac(sha3-512)");
		break;

	case 150:
		ret += tcrypt_test("ansi_cprng");
		break;

	case 151:
		ret += tcrypt_test("rfc4106(gcm(aes))");
		break;

	case 152:
		ret += tcrypt_test("rfc4543(gcm(aes))");
		break;

	case 153:
		ret += tcrypt_test("cmac(aes)");
		break;

	case 154:
		ret += tcrypt_test("cmac(des3_ede)");
		break;

	case 155:
		ret += tcrypt_test("authenc(hmac(sha1),cbc(aes))");
		break;

	case 156:
		ret += tcrypt_test("authenc(hmac(md5),ecb(cipher_null))");
		break;

	case 157:
		ret += tcrypt_test("authenc(hmac(sha1),ecb(cipher_null))");
		break;
	case 181:
		ret += tcrypt_test("authenc(hmac(sha1),cbc(des))");
		break;
	case 182:
		ret += tcrypt_test("authenc(hmac(sha1),cbc(des3_ede))");
		break;
	case 183:
		ret += tcrypt_test("authenc(hmac(sha224),cbc(des))");
		break;
	case 184:
		ret += tcrypt_test("authenc(hmac(sha224),cbc(des3_ede))");
		break;
	case 185:
		ret += tcrypt_test("authenc(hmac(sha256),cbc(des))");
		break;
	case 186:
		ret += tcrypt_test("authenc(hmac(sha256),cbc(des3_ede))");
		break;
	case 187:
		ret += tcrypt_test("authenc(hmac(sha384),cbc(des))");
		break;
	case 188:
		ret += tcrypt_test("authenc(hmac(sha384),cbc(des3_ede))");
		break;
	case 189:
		ret += tcrypt_test("authenc(hmac(sha512),cbc(des))");
		break;
	case 190:
		ret += tcrypt_test("authenc(hmac(sha512),cbc(des3_ede))");
		break;
	case 191:
		ret += tcrypt_test("ecb(sm4)");
		break;
	case 200:
		test_cipher_speed("ecb(aes)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ecb(aes)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cbc(aes)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cbc(aes)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("lrw(aes)", ENCRYPT, sec, NULL, 0,
				speed_template_32_40_48);
		test_cipher_speed("lrw(aes)", DECRYPT, sec, NULL, 0,
				speed_template_32_40_48);
		test_cipher_speed("xts(aes)", ENCRYPT, sec, NULL, 0,
				speed_template_32_64);
		test_cipher_speed("xts(aes)", DECRYPT, sec, NULL, 0,
				speed_template_32_64);
		test_cipher_speed("cts(cbc(aes))", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cts(cbc(aes))", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ctr(aes)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ctr(aes)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cfb(aes)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cfb(aes)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		break;

	case 201:
		test_cipher_speed("ecb(des3_ede)", ENCRYPT, sec,
				des3_speed_template, DES3_SPEED_VECTORS,
				speed_template_24);
		test_cipher_speed("ecb(des3_ede)", DECRYPT, sec,
				des3_speed_template, DES3_SPEED_VECTORS,
				speed_template_24);
		test_cipher_speed("cbc(des3_ede)", ENCRYPT, sec,
				des3_speed_template, DES3_SPEED_VECTORS,
				speed_template_24);
		test_cipher_speed("cbc(des3_ede)", DECRYPT, sec,
				des3_speed_template, DES3_SPEED_VECTORS,
				speed_template_24);
		test_cipher_speed("ctr(des3_ede)", ENCRYPT, sec,
				des3_speed_template, DES3_SPEED_VECTORS,
				speed_template_24);
		test_cipher_speed("ctr(des3_ede)", DECRYPT, sec,
				des3_speed_template, DES3_SPEED_VECTORS,
				speed_template_24);
		break;

	case 202:
		test_cipher_speed("ecb(twofish)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ecb(twofish)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cbc(twofish)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cbc(twofish)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ctr(twofish)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ctr(twofish)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("lrw(twofish)", ENCRYPT, sec, NULL, 0,
				speed_template_32_40_48);
		test_cipher_speed("lrw(twofish)", DECRYPT, sec, NULL, 0,
				speed_template_32_40_48);
		test_cipher_speed("xts(twofish)", ENCRYPT, sec, NULL, 0,
				speed_template_32_48_64);
		test_cipher_speed("xts(twofish)", DECRYPT, sec, NULL, 0,
				speed_template_32_48_64);
		break;

	case 203:
		test_cipher_speed("ecb(blowfish)", ENCRYPT, sec, NULL, 0,
				  speed_template_8_32);
		test_cipher_speed("ecb(blowfish)", DECRYPT, sec, NULL, 0,
				  speed_template_8_32);
		test_cipher_speed("cbc(blowfish)", ENCRYPT, sec, NULL, 0,
				  speed_template_8_32);
		test_cipher_speed("cbc(blowfish)", DECRYPT, sec, NULL, 0,
				  speed_template_8_32);
		test_cipher_speed("ctr(blowfish)", ENCRYPT, sec, NULL, 0,
				  speed_template_8_32);
		test_cipher_speed("ctr(blowfish)", DECRYPT, sec, NULL, 0,
				  speed_template_8_32);
		break;

	case 204:
		test_cipher_speed("ecb(des)", ENCRYPT, sec, NULL, 0,
				  speed_template_8);
		test_cipher_speed("ecb(des)", DECRYPT, sec, NULL, 0,
				  speed_template_8);
		test_cipher_speed("cbc(des)", ENCRYPT, sec, NULL, 0,
				  speed_template_8);
		test_cipher_speed("cbc(des)", DECRYPT, sec, NULL, 0,
				  speed_template_8);
		break;

	case 205:
		test_cipher_speed("ecb(camellia)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ecb(camellia)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cbc(camellia)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("cbc(camellia)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ctr(camellia)", ENCRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("ctr(camellia)", DECRYPT, sec, NULL, 0,
				speed_template_16_24_32);
		test_cipher_speed("lrw(camellia)", ENCRYPT, sec, NULL, 0,
				speed_template_32_40_48);
		test_cipher_speed("lrw(camellia)", DECRYPT, sec, NULL, 0,
				speed_template_32_40_48);
		test_cipher_speed("xts(camellia)", ENCRYPT, sec, NULL, 0,
				speed_template_32_48_64);
		test_cipher_speed("xts(camellia)", DECRYPT, sec, NULL, 0,
				speed_template_32_48_64);
		break;

	case 206:
		test_cipher_speed("salsa20", ENCRYPT, sec, NULL, 0,
				  speed_template_16_32);
		break;

	case 207:
		test_cipher_speed("ecb(serpent)", ENCRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("ecb(serpent)", DECRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("cbc(serpent)", ENCRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("cbc(serpent)", DECRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("ctr(serpent)", ENCRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("ctr(serpent)", DECRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("lrw(serpent)", ENCRYPT, sec, NULL, 0,
				  speed_template_32_48);
		test_cipher_speed("lrw(serpent)", DECRYPT, sec, NULL, 0,
				  speed_template_32_48);
		test_cipher_speed("xts(serpent)", ENCRYPT, sec, NULL, 0,
				  speed_template_32_64);
		test_cipher_speed("xts(serpent)", DECRYPT, sec, NULL, 0,
				  speed_template_32_64);
		break;

	case 208:
		test_cipher_speed("ecb(arc4)", ENCRYPT, sec, NULL, 0,
				  speed_template_8);
		break;

	case 209:
		test_cipher_speed("ecb(cast5)", ENCRYPT, sec, NULL, 0,
				  speed_template_8_16);
		test_cipher_speed("ecb(cast5)", DECRYPT, sec, NULL, 0,
				  speed_template_8_16);
		test_cipher_speed("cbc(cast5)", ENCRYPT, sec, NULL, 0,
				  speed_template_8_16);
		test_cipher_speed("cbc(cast5)", DECRYPT, sec, NULL, 0,
				  speed_template_8_16);
		test_cipher_speed("ctr(cast5)", ENCRYPT, sec, NULL, 0,
				  speed_template_8_16);
		test_cipher_speed("ctr(cast5)", DECRYPT, sec, NULL, 0,
				  speed_template_8_16);
		break;

	case 210:
		test_cipher_speed("ecb(cast6)", ENCRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("ecb(cast6)", DECRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("cbc(cast6)", ENCRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("cbc(cast6)", DECRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("ctr(cast6)", ENCRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("ctr(cast6)", DECRYPT, sec, NULL, 0,
				  speed_template_16_32);
		test_cipher_speed("lrw(cast6)", ENCRYPT, sec, NULL, 0,
				  speed_template_32_48);
		test_cipher_speed("lrw(cast6)", DECRYPT, sec, NULL, 0,
				  speed_template_32_48);
		test_cipher_speed("xts(cast6)", ENCRYPT, sec, NULL, 0,
				  speed_template_32_64);
		test_cipher_speed("xts(cast6)", DECRYPT, sec, NULL, 0,
				  speed_template_32_64);
		break;

	case 211:
		test_aead_speed("rfc4106(gcm(aes))", ENCRYPT, sec,
				NULL, 0, 16, 16, aead_speed_template_20);
		test_aead_speed("gcm(aes)", ENCRYPT, sec,
				NULL, 0, 16, 8, speed_template_16_24_32);
		test_aead_speed("rfc4106(gcm(aes))", DECRYPT, sec,
				NULL, 0, 16, 16, aead_speed_template_20);
		test_aead_speed("gcm(aes)", DECRYPT, sec,
				NULL, 0, 16, 8, speed_template_16_24_32);
		break;

	case 212:
		test_aead_speed("rfc4309(ccm(aes))", ENCRYPT, sec,
				NULL, 0, 16, 16, aead_speed_template_19);
		test_aead_speed("rfc4309(ccm(aes))", DECRYPT, sec,
				NULL, 0, 16, 16, aead_speed_template_19);
		break;

	case 213:
		test_aead_speed("rfc7539esp(chacha20,poly1305)", ENCRYPT, sec,
				NULL, 0, 16, 8, aead_speed_template_36);
		test_aead_speed("rfc7539esp(chacha20,poly1305)", DECRYPT, sec,
				NULL, 0, 16, 8, aead_speed_template_36);
		break;

	case 214:
		test_cipher_speed("chacha20", ENCRYPT, sec, NULL, 0,
				  speed_template_32);
		break;

	case 215:
		test_mb_aead_speed("rfc4106(gcm(aes))", ENCRYPT, sec, NULL,
				   0, 16, 16, aead_speed_template_20, num_mb);
		test_mb_aead_speed("gcm(aes)", ENCRYPT, sec, NULL, 0, 16, 8,
				   speed_template_16_24_32, num_mb);
		test_mb_aead_speed("rfc4106(gcm(aes))", DECRYPT, sec, NULL,
				   0, 16, 16, aead_speed_template_20, num_mb);
		test_mb_aead_speed("gcm(aes)", DECRYPT, sec, NULL, 0, 16, 8,
				   speed_template_16_24_32, num_mb);
		break;

	case 216:
		test_mb_aead_speed("rfc4309(ccm(aes))", ENCRYPT, sec, NULL, 0,
				   16, 16, aead_speed_template_19, num_mb);
		test_mb_aead_speed("rfc4309(ccm(aes))", DECRYPT, sec, NULL, 0,
				   16, 16, aead_speed_template_19, num_mb);
		break;

	case 217:
		test_mb_aead_speed("rfc7539esp(chacha20,poly1305)", ENCRYPT,
				   sec, NULL, 0, 16, 8, aead_speed_template_36,
				   num_mb);
		test_mb_aead_speed("rfc7539esp(chacha20,poly1305)", DECRYPT,
				   sec, NULL, 0, 16, 8, aead_speed_template_36,
				   num_mb);
		break;

	case 300:
		if (alg) {
			test_hash_speed(alg, sec, generic_hash_speed_template);
			break;
		}
		/* fall through */
	case 301:
		test_hash_speed("md4", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 302:
		test_hash_speed("md5", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 303:
		test_hash_speed("sha1", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 304:
		test_hash_speed("sha256", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 305:
		test_hash_speed("sha384", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 306:
		test_hash_speed("sha512", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 307:
		test_hash_speed("wp256", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 308:
		test_hash_speed("wp384", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 309:
		test_hash_speed("wp512", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 310:
		test_hash_speed("tgr128", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 311:
		test_hash_speed("tgr160", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 312:
		test_hash_speed("tgr192", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 313:
		test_hash_speed("sha224", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 314:
		test_hash_speed("rmd128", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 315:
		test_hash_speed("rmd160", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 316:
		test_hash_speed("rmd256", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 317:
		test_hash_speed("rmd320", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 318:
		test_hash_speed("ghash-generic", sec, hash_speed_template_16);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 319:
		test_hash_speed("crc32c", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 320:
		test_hash_speed("crct10dif", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 321:
		test_hash_speed("poly1305", sec, poly1305_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 322:
		test_hash_speed("sha3-224", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 323:
		test_hash_speed("sha3-256", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 324:
		test_hash_speed("sha3-384", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 325:
		test_hash_speed("sha3-512", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 326:
		test_hash_speed("sm3", sec, generic_hash_speed_template);
		if (mode > 300 && mode < 400) break;
		/* fall through */
	case 399:
		break;

	case 400:
		if (alg) {
			test_ahash_speed(alg, sec, generic_hash_speed_template);
			break;
		}
		/* fall through */
	case 401:
		test_ahash_speed("md4", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 402:
		test_ahash_speed("md5", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 403:
		test_ahash_speed("sha1", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 404:
		test_ahash_speed("sha256", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 405:
		test_ahash_speed("sha384", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 406:
		test_ahash_speed("sha512", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 407:
		test_ahash_speed("wp256", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 408:
		test_ahash_speed("wp384", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 409:
		test_ahash_speed("wp512", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 410:
		test_ahash_speed("tgr128", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 411:
		test_ahash_speed("tgr160", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 412:
		test_ahash_speed("tgr192", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 413:
		test_ahash_speed("sha224", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 414:
		test_ahash_speed("rmd128", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 415:
		test_ahash_speed("rmd160", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 416:
		test_ahash_speed("rmd256", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 417:
		test_ahash_speed("rmd320", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 418:
		test_ahash_speed("sha3-224", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 419:
		test_ahash_speed("sha3-256", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 420:
		test_ahash_speed("sha3-384", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 421:
		test_ahash_speed("sha3-512", sec, generic_hash_speed_template);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 422:
		test_mb_ahash_speed("sha1", sec, generic_hash_speed_template,
				    num_mb);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 423:
		test_mb_ahash_speed("sha256", sec, generic_hash_speed_template,
				    num_mb);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 424:
		test_mb_ahash_speed("sha512", sec, generic_hash_speed_template,
				    num_mb);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 425:
		test_mb_ahash_speed("sm3", sec, generic_hash_speed_template,
				    num_mb);
		if (mode > 400 && mode < 500) break;
		/* fall through */
	case 499:
		break;

	case 500:
		test_acipher_speed("ecb(aes)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ecb(aes)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("cbc(aes)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("cbc(aes)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("lrw(aes)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_40_48);
		test_acipher_speed("lrw(aes)", DECRYPT, sec, NULL, 0,
				   speed_template_32_40_48);
		test_acipher_speed("xts(aes)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_64);
		test_acipher_speed("xts(aes)", DECRYPT, sec, NULL, 0,
				   speed_template_32_64);
		test_acipher_speed("cts(cbc(aes))", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("cts(cbc(aes))", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ctr(aes)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ctr(aes)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("cfb(aes)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("cfb(aes)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ofb(aes)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ofb(aes)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("rfc3686(ctr(aes))", ENCRYPT, sec, NULL, 0,
				   speed_template_20_28_36);
		test_acipher_speed("rfc3686(ctr(aes))", DECRYPT, sec, NULL, 0,
				   speed_template_20_28_36);
		break;

	case 501:
		test_acipher_speed("ecb(des3_ede)", ENCRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		test_acipher_speed("ecb(des3_ede)", DECRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		test_acipher_speed("cbc(des3_ede)", ENCRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		test_acipher_speed("cbc(des3_ede)", DECRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		test_acipher_speed("cfb(des3_ede)", ENCRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		test_acipher_speed("cfb(des3_ede)", DECRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		test_acipher_speed("ofb(des3_ede)", ENCRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		test_acipher_speed("ofb(des3_ede)", DECRYPT, sec,
				   des3_speed_template, DES3_SPEED_VECTORS,
				   speed_template_24);
		break;

	case 502:
		test_acipher_speed("ecb(des)", ENCRYPT, sec, NULL, 0,
				   speed_template_8);
		test_acipher_speed("ecb(des)", DECRYPT, sec, NULL, 0,
				   speed_template_8);
		test_acipher_speed("cbc(des)", ENCRYPT, sec, NULL, 0,
				   speed_template_8);
		test_acipher_speed("cbc(des)", DECRYPT, sec, NULL, 0,
				   speed_template_8);
		test_acipher_speed("cfb(des)", ENCRYPT, sec, NULL, 0,
				   speed_template_8);
		test_acipher_speed("cfb(des)", DECRYPT, sec, NULL, 0,
				   speed_template_8);
		test_acipher_speed("ofb(des)", ENCRYPT, sec, NULL, 0,
				   speed_template_8);
		test_acipher_speed("ofb(des)", DECRYPT, sec, NULL, 0,
				   speed_template_8);
		break;

	case 503:
		test_acipher_speed("ecb(serpent)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ecb(serpent)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("cbc(serpent)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("cbc(serpent)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ctr(serpent)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ctr(serpent)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("lrw(serpent)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_48);
		test_acipher_speed("lrw(serpent)", DECRYPT, sec, NULL, 0,
				   speed_template_32_48);
		test_acipher_speed("xts(serpent)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_64);
		test_acipher_speed("xts(serpent)", DECRYPT, sec, NULL, 0,
				   speed_template_32_64);
		break;

	case 504:
		test_acipher_speed("ecb(twofish)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ecb(twofish)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("cbc(twofish)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("cbc(twofish)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ctr(twofish)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("ctr(twofish)", DECRYPT, sec, NULL, 0,
				   speed_template_16_24_32);
		test_acipher_speed("lrw(twofish)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_40_48);
		test_acipher_speed("lrw(twofish)", DECRYPT, sec, NULL, 0,
				   speed_template_32_40_48);
		test_acipher_speed("xts(twofish)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_48_64);
		test_acipher_speed("xts(twofish)", DECRYPT, sec, NULL, 0,
				   speed_template_32_48_64);
		break;

	case 505:
		test_acipher_speed("ecb(arc4)", ENCRYPT, sec, NULL, 0,
				   speed_template_8);
		break;

	case 506:
		test_acipher_speed("ecb(cast5)", ENCRYPT, sec, NULL, 0,
				   speed_template_8_16);
		test_acipher_speed("ecb(cast5)", DECRYPT, sec, NULL, 0,
				   speed_template_8_16);
		test_acipher_speed("cbc(cast5)", ENCRYPT, sec, NULL, 0,
				   speed_template_8_16);
		test_acipher_speed("cbc(cast5)", DECRYPT, sec, NULL, 0,
				   speed_template_8_16);
		test_acipher_speed("ctr(cast5)", ENCRYPT, sec, NULL, 0,
				   speed_template_8_16);
		test_acipher_speed("ctr(cast5)", DECRYPT, sec, NULL, 0,
				   speed_template_8_16);
		break;

	case 507:
		test_acipher_speed("ecb(cast6)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ecb(cast6)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("cbc(cast6)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("cbc(cast6)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ctr(cast6)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ctr(cast6)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("lrw(cast6)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_48);
		test_acipher_speed("lrw(cast6)", DECRYPT, sec, NULL, 0,
				   speed_template_32_48);
		test_acipher_speed("xts(cast6)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_64);
		test_acipher_speed("xts(cast6)", DECRYPT, sec, NULL, 0,
				   speed_template_32_64);
		break;

	case 508:
		test_acipher_speed("ecb(camellia)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ecb(camellia)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("cbc(camellia)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("cbc(camellia)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ctr(camellia)", ENCRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("ctr(camellia)", DECRYPT, sec, NULL, 0,
				   speed_template_16_32);
		test_acipher_speed("lrw(camellia)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_48);
		test_acipher_speed("lrw(camellia)", DECRYPT, sec, NULL, 0,
				   speed_template_32_48);
		test_acipher_speed("xts(camellia)", ENCRYPT, sec, NULL, 0,
				   speed_template_32_64);
		test_acipher_speed("xts(camellia)", DECRYPT, sec, NULL, 0,
				   speed_template_32_64);
		break;

	case 509:
		test_acipher_speed("ecb(blowfish)", ENCRYPT, sec, NULL, 0,
				   speed_template_8_32);
		test_acipher_speed("ecb(blowfish)", DECRYPT, sec, NULL, 0,
				   speed_template_8_32);
		test_acipher_speed("cbc(blowfish)", ENCRYPT, sec, NULL, 0,
				   speed_template_8_32);
		test_acipher_speed("cbc(blowfish)", DECRYPT, sec, NULL, 0,
				   speed_template_8_32);
		test_acipher_speed("ctr(blowfish)", ENCRYPT, sec, NULL, 0,
				   speed_template_8_32);
		test_acipher_speed("ctr(blowfish)", DECRYPT, sec, NULL, 0,
				   speed_template_8_32);
		break;

	case 600:
		test_mb_skcipher_speed("ecb(aes)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ecb(aes)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(aes)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(aes)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("lrw(aes)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_40_48, num_mb);
		test_mb_skcipher_speed("lrw(aes)", DECRYPT, sec, NULL, 0,
				       speed_template_32_40_48, num_mb);
		test_mb_skcipher_speed("xts(aes)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		test_mb_skcipher_speed("xts(aes)", DECRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		test_mb_skcipher_speed("cts(cbc(aes))", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("cts(cbc(aes))", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(aes)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(aes)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("cfb(aes)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("cfb(aes)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ofb(aes)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ofb(aes)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("rfc3686(ctr(aes))", ENCRYPT, sec, NULL,
				       0, speed_template_20_28_36, num_mb);
		test_mb_skcipher_speed("rfc3686(ctr(aes))", DECRYPT, sec, NULL,
				       0, speed_template_20_28_36, num_mb);
		break;

	case 601:
		test_mb_skcipher_speed("ecb(des3_ede)", ENCRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		test_mb_skcipher_speed("ecb(des3_ede)", DECRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		test_mb_skcipher_speed("cbc(des3_ede)", ENCRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		test_mb_skcipher_speed("cbc(des3_ede)", DECRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		test_mb_skcipher_speed("cfb(des3_ede)", ENCRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		test_mb_skcipher_speed("cfb(des3_ede)", DECRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		test_mb_skcipher_speed("ofb(des3_ede)", ENCRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		test_mb_skcipher_speed("ofb(des3_ede)", DECRYPT, sec,
				       des3_speed_template, DES3_SPEED_VECTORS,
				       speed_template_24, num_mb);
		break;

	case 602:
		test_mb_skcipher_speed("ecb(des)", ENCRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		test_mb_skcipher_speed("ecb(des)", DECRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		test_mb_skcipher_speed("cbc(des)", ENCRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		test_mb_skcipher_speed("cbc(des)", DECRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		test_mb_skcipher_speed("cfb(des)", ENCRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		test_mb_skcipher_speed("cfb(des)", DECRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		test_mb_skcipher_speed("ofb(des)", ENCRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		test_mb_skcipher_speed("ofb(des)", DECRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		break;

	case 603:
		test_mb_skcipher_speed("ecb(serpent)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ecb(serpent)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("cbc(serpent)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("cbc(serpent)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ctr(serpent)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ctr(serpent)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("lrw(serpent)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_48, num_mb);
		test_mb_skcipher_speed("lrw(serpent)", DECRYPT, sec, NULL, 0,
				       speed_template_32_48, num_mb);
		test_mb_skcipher_speed("xts(serpent)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		test_mb_skcipher_speed("xts(serpent)", DECRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		break;

	case 604:
		test_mb_skcipher_speed("ecb(twofish)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ecb(twofish)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(twofish)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("cbc(twofish)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(twofish)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("ctr(twofish)", DECRYPT, sec, NULL, 0,
				       speed_template_16_24_32, num_mb);
		test_mb_skcipher_speed("lrw(twofish)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_40_48, num_mb);
		test_mb_skcipher_speed("lrw(twofish)", DECRYPT, sec, NULL, 0,
				       speed_template_32_40_48, num_mb);
		test_mb_skcipher_speed("xts(twofish)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_48_64, num_mb);
		test_mb_skcipher_speed("xts(twofish)", DECRYPT, sec, NULL, 0,
				       speed_template_32_48_64, num_mb);
		break;

	case 605:
		test_mb_skcipher_speed("ecb(arc4)", ENCRYPT, sec, NULL, 0,
				       speed_template_8, num_mb);
		break;

	case 606:
		test_mb_skcipher_speed("ecb(cast5)", ENCRYPT, sec, NULL, 0,
				       speed_template_8_16, num_mb);
		test_mb_skcipher_speed("ecb(cast5)", DECRYPT, sec, NULL, 0,
				       speed_template_8_16, num_mb);
		test_mb_skcipher_speed("cbc(cast5)", ENCRYPT, sec, NULL, 0,
				       speed_template_8_16, num_mb);
		test_mb_skcipher_speed("cbc(cast5)", DECRYPT, sec, NULL, 0,
				       speed_template_8_16, num_mb);
		test_mb_skcipher_speed("ctr(cast5)", ENCRYPT, sec, NULL, 0,
				       speed_template_8_16, num_mb);
		test_mb_skcipher_speed("ctr(cast5)", DECRYPT, sec, NULL, 0,
				       speed_template_8_16, num_mb);
		break;

	case 607:
		test_mb_skcipher_speed("ecb(cast6)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ecb(cast6)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("cbc(cast6)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("cbc(cast6)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ctr(cast6)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ctr(cast6)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("lrw(cast6)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_48, num_mb);
		test_mb_skcipher_speed("lrw(cast6)", DECRYPT, sec, NULL, 0,
				       speed_template_32_48, num_mb);
		test_mb_skcipher_speed("xts(cast6)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		test_mb_skcipher_speed("xts(cast6)", DECRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		break;

	case 608:
		test_mb_skcipher_speed("ecb(camellia)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ecb(camellia)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("cbc(camellia)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("cbc(camellia)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ctr(camellia)", ENCRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("ctr(camellia)", DECRYPT, sec, NULL, 0,
				       speed_template_16_32, num_mb);
		test_mb_skcipher_speed("lrw(camellia)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_48, num_mb);
		test_mb_skcipher_speed("lrw(camellia)", DECRYPT, sec, NULL, 0,
				       speed_template_32_48, num_mb);
		test_mb_skcipher_speed("xts(camellia)", ENCRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		test_mb_skcipher_speed("xts(camellia)", DECRYPT, sec, NULL, 0,
				       speed_template_32_64, num_mb);
		break;

	case 609:
		test_mb_skcipher_speed("ecb(blowfish)", ENCRYPT, sec, NULL, 0,
				       speed_template_8_32, num_mb);
		test_mb_skcipher_speed("ecb(blowfish)", DECRYPT, sec, NULL, 0,
				       speed_template_8_32, num_mb);
		test_mb_skcipher_speed("cbc(blowfish)", ENCRYPT, sec, NULL, 0,
				       speed_template_8_32, num_mb);
		test_mb_skcipher_speed("cbc(blowfish)", DECRYPT, sec, NULL, 0,
				       speed_template_8_32, num_mb);
		test_mb_skcipher_speed("ctr(blowfish)", ENCRYPT, sec, NULL, 0,
				       speed_template_8_32, num_mb);
		test_mb_skcipher_speed("ctr(blowfish)", DECRYPT, sec, NULL, 0,
				       speed_template_8_32, num_mb);
		break;

	case 1000:
		test_available();
		break;
	}

	return ret;
}